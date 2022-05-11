#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <limits.h>

#define GRANTED 0

#define FAIRLEARNERS 0
#define FASTLEARNERS 1
#define ARRIVALORDER 2
#define PRELEARNERS 3

#define timeType unsigned long  //the type we store time in, used for metric
#define timeTypeMax ULONG_MAX

int scheduler_metric; 

int breads = 0;     // # of breads made
int maxBread;
int NBApprentices; // Number of apprentices :: int
pthread_t *threadIndexes; // Array keeping track of apprentice IDs :: Array of int
timeType *interested_array; // Array of size NBApprentices where apprentices can anounce interest in accessing the inventory :: Array of int
// Node *inventory; // Inventory :: Dynamic array of linked lists
pthread_mutex_t mutex_inventory; // Mutex to ensure mutual exclusive access to inventory :: pthread_sem_t
pthread_mutex_t *mutA; // Mutexes and condition variable (1 for each apprentice) to wake it up once they're allow to access the inventory

sem_t *semA;
sem_t bakers;
pthread_cond_t *condT; // Condition variable to wake up teacher :: pthread_cond_t

struct timeval tvbase, tvnow;

void *baker(void *j){
	while (breads < maxBread) {
	
		//printf("baker started loop\n");
	
		timeType max=0;
		int j=-1;//the next A to be allowed into Inv
		//printf("baker\n");
		for (int i=0; i<NBApprentices; i++) { //select which A is worthy to be next
			if (interested_array[i] > max) { 
				j = i;
				max = interested_array[i];
			}
			//printf("cmp %lu > %lu\n", interested_array[i] ,max);
			
		}
		
		//printf("baker ended loop\n");
		
		if (j>=0) {
			//wakre up A
			interested_array[j]=0;
			printf("baker wakes up %d with metric: %lu\n", j, max);
			sem_post(&semA[j]);
			
			//baker sleep until that one is finished
			//printf("baker sleeping");
			sem_wait(&bakers);
		}
		

	}
	//wake all A up
	for(int i = 0; i < NBApprentices; i++){
    	sem_post(&semA[i]);
    }
	
	int ret = 0;
	pthread_exit(&ret);
}


void access_inventory(int i){
    //printf("Apprentic %d accesses the inventory.\n",i);
}

void *apprentice(void *j){
    /*
    - Say hello
    - Try access inventory:
        - check mutex on the resource you desire using trylock
            - if +: Go and get the resource and then free the mutex
            - if -: Insert your timestamp in interested array and sleep on your semaphore
                    As soon as your woken up by teacher, you get the mutex.
    - Bake bread
    - Repeat
    */

    int i = (int ) j; // Apprentice ID
    int abread = 0;
    

    while(breads<maxBread){
        //printf("Apprentice %d wants to access the inventory.\n",i);
		
		gettimeofday(&tvnow, NULL);
	
	    timeType metric;
	    if (scheduler_metric == ARRIVALORDER) {//arrival order
	    	
	    	metric = timeTypeMax - (tvnow.tv_sec - tvbase.tv_sec)*1000000 - (tvnow.tv_usec - tvbase.tv_usec);
	    	//printf("%lu = %lu  . %lu\n", metric, tvnow.tv_sec, tvnow.tv_usec);  
	    } else if (scheduler_metric == FASTLEARNERS) {//fast learners
	    	metric = abread;
	    } else if (scheduler_metric == FAIRLEARNERS) {//fair learners
	    	metric = timeTypeMax - abread;
	    } else if (scheduler_metric == PRELEARNERS) {//pre defined learners
	    	metric = i;
	    } 
	    
	    
	    interested_array[i] = metric; // Announce interest
	    
	     // Wait until it's my turn
	    //printf("%d is sleeping\n", i);
	    sem_wait(&semA[i]);//sleep on own semaphore
			printf("Apprentice %d woke up\n", i);

	    pthread_mutex_lock(&mutex_inventory);//TODO dynamic inventory
	    access_inventory(i);
	    if (breads>=maxBread) {
	    	pthread_mutex_unlock(&mutex_inventory);	
	    	printf("Apprentice %d stopped\n", i);
	    	pthread_exit(NULL);
	    }
	    breads++;
	    abread++;
	    printf("Apprentice %d made bread #%d.\n",i, breads);
	    pthread_mutex_unlock(&mutex_inventory);
	    
	    //tell baker you are out again
	    sem_post(&bakers);
        
		sleep(rand()%3+1);
        
        
    }
}



int main(int argc, char const *argv[]){
srand(time(NULL));
gettimeofday(&tvbase, NULL);
//gettimeofday(&tvnow, NULL);
printf("v3\n");

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
    if (argc == 1) {//Default valaues
        NBApprentices = 30;
        maxBread = 100;
        scheduler_metric = FASTLEARNERS;
        //TODO get metric
    } else if (argc == 2) {// one argument given = # chairs
    	maxBread = 100;
        NBApprentices = atoi(argv[1]);
        if (NBApprentices < 1) {
            printf("Please input a positive number for the # Apprentices as first argument\n");
        	return;
        }
    } else if (argc == 3) {// 2 argument given = # chairs # maxBreads
    	maxBread = atoi(argv[2]);
        NBApprentices = atoi(argv[1]);
        if (NBApprentices < 1 || maxBread < 1) {
            printf("Please input a positive number for the # Apprentices as first argument\nand for the maximum amount of breads to be made as second arg\n");
            return;
        }
    }//TODO TEST SCENARIO TWO A AT A TIME
    

    interested_array = malloc(NBApprentices*sizeof(timeType));
    threadIndexes = malloc(NBApprentices*sizeof(pthread_t));
    mutA = malloc(NBApprentices*sizeof(pthread_mutex_t));
    semA = malloc(NBApprentices*sizeof(sem_t));


    /* INITIALIZE MUTEX AND CONDITION VARIABLES */
    pthread_mutex_init(&mutex_inventory, NULL);
    pthread_cond_init(&condT, NULL);
    sem_init(&bakers, 0, 0);

    for(int i = 0; i < NBApprentices; i++){
        pthread_mutex_init(&mutA[i], NULL);
        sem_init(&semA[i], 0, 0);
        interested_array[i]=-1;
    }

	pthread_t bakert;
	pthread_create(&bakert, NULL, baker, (void *) 0);
    /* CREATE THREADS REPRESENTING APPRENTICES */
    for (int i = 0; i < NBApprentices; i++){
        if(pthread_create(&threadIndexes[i], NULL, apprentice, (void *) i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Apprentice %d created!\n", i);
        }
    }

	//join threads so we see the printed output
	for (int i=0; i<NBApprentices; i++) { 
		pthread_join(threadIndexes[i], NULL);//TODO join
		printf("joined a thread\n");
	}

	int be = pthread_join(bakert, NULL);
	printf("baker joined %d\n", be);
    return 0;
}
