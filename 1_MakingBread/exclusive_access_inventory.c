#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <limits.h>

#include "inventory_BinTree.h"

#define FAIRLEARNERS 0
#define FASTLEARNERS 1
#define ARRIVALORDER 2
#define PRELEARNERS 3

int SCENARIO;
#define SCENARIO1 1 //2 A add same Item
#define SCENARIO2 2 //2 A access same Item
#define SCENARIO3 3 //add and another retrieve the sam eitem at the sam etime

#define timeType unsigned long  //the type we store time in, used for metric
#define timeTypeMax ULONG_MAX

int scheduler_metric; 

int breads = 0;     // # of breads made
int maxBread;
int NBApprentices; // Number of apprentices :: int
int NBIngredients; // Number of ingreditents :: int
// char* ingredientNames[]; // Names of indredients :: Array of strings
pthread_t *threadIndexes; // Array keeping track of apprentice IDs :: Array of int
timeType *interested_array; // Array of size NBApprentices where apprentices can anounce interest in accessing the inventory :: Array of int
// IngredNode *inventory; // Inventory :: Binary Tree of linked lists
pthread_mutex_t mutex_inventory; // Mutex to ensure mutual exclusive access to inventory :: pthread_sem_t
pthread_mutex_t *mutA; // Mutexes and condition variable (1 for each apprentice) to wake it up once they're allow to access the inventory

sem_t *semA;
sem_t bakers;
sem_t semS;

struct timeval tvbase, tvnow;

void *baker(void *j){
	int scenario2alt=0;
	int scenario2j;
	while (breads < maxBread) {
	
		//printf("baker started loop\n");
	
		timeType min=timeTypeMax;
		int j=-1;//the next A to be allowed into Inv
		//printf("baker\n");
		for (int i=0; i<NBApprentices; i++) { //select which A is worthy to be next
			if (interested_array[i] < min) { 
				j = i;
				min = interested_array[i];
			}
			//printf("cmp %lu > %lu\n", interested_array[i] ,min);
			
		}
		
		//printf("baker ended loop %d\n", j);
		
		if (j>=0) {

			//scenario handler
			if (SCENARIO == SCENARIO2 && scenario2alt == 0) {
				
				scenario2alt = 1;
				scenario2j = j;
				interested_array[j]=timeTypeMax;
				continue;//dont sleep for one loop

			} else if (SCENARIO == SCENARIO2) {
				scenario2alt = 0; //to sleep after waking up 2 apprentices
				//wakre up both A
				interested_array[j]=timeTypeMax;
				printf("Baker wakes up %d and %d simultaneously\n", j, scenario2j);
				sem_post(&semA[j]);
				sem_post(&semA[scenario2j]);
				
				//baker sleep until that one is finished
				//printf("baker sleeping");
				sem_wait(&bakers);
				sem_wait(&bakers);
				continue;
			}

			//wakre up A
			interested_array[j]=timeTypeMax;
			printf("Baker wakes up %d with metric: %lu\n", j, min);
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

// void *shopper(){
// 	while (breads < maxBread){
// 		sem_wait(semS);
// 		// restore_inventory();
// 	}
// }


void access_inventory(int i){
	// TODO Implement inventory
	/*
	- Take ingredients
	- If one ingredient missing, wake up shopper and make it restore inventory.	
	*/   
    printf("Apprentice %d accesses the inventory.\n",i);
}

void *apprentice(void *j){

    int i = (int ) j; // Apprentice ID
    int abread = 0;
    
	timeType metric;
    while(breads < maxBread){
        //printf("Apprentice %d wants to access the inventory.\n",i);
		
		gettimeofday(&tvnow, NULL);
	
	    
	    if (scheduler_metric == ARRIVALORDER) {//arrival order
	    	metric = (tvnow.tv_sec - tvbase.tv_sec)*1000000 + (tvnow.tv_usec - tvbase.tv_usec);
	    	//printf("%lu = %lu  . %lu\n", metric, tvnow.tv_sec, tvnow.tv_usec);  
	    } else if (scheduler_metric == FASTLEARNERS) {//fast learners
	    	metric = timeTypeMax - abread - 1;
			//printf("%d metric: %lu\n", i, metric);
	    } else if (scheduler_metric == FAIRLEARNERS) {//fair learners
	    	metric = abread;
	    } else if (scheduler_metric == PRELEARNERS) {//pre defined learners
	    	metric = i;
	    } 
	    
	    
	    interested_array[i] = metric; // Announce interest
	    
	     // Wait until it's my turn
	    //printf("%d is sleeping\n", i);
	    sem_wait(&semA[i]);//sleep on own semaphore
		printf("     Apprentice %d woke up\n", i);

	    pthread_mutex_lock(&mutex_inventory);// TODO dynamic inventory
	    access_inventory(i);
	    if (breads>=maxBread) {
	    	pthread_mutex_unlock(&mutex_inventory);	
	    	printf("     Apprentice %d made bread #%d (her %dth bread).\n",i, breads, abread);
	    	pthread_exit(NULL);
	    }
	    breads++;
	    abread++;
	    printf("     Apprentice %d made bread #%d (her %dth bread).\n",i, breads, abread);
	    pthread_mutex_unlock(&mutex_inventory);
	    
	    //tell baker you are out again
	    sem_post(&bakers);
        
		sleep(rand()%3+1);
        
        
    }
    printf("     Apprentice %d made %d breads today\n", i, abread);
}


int run (int nbAppr, int maxB, int nbIngr, char* ingNames[], int metric, int scen){
	srand(time(NULL));
	gettimeofday(&tvbase, NULL);
	//gettimeofday(&tvnow, NULL);
	printf("v3\n");

    // /* INITIALIZE VARIABLES BASED ON USER INPUT */

    // if (argc == 2) {// one argument given = # chairs
    // 	maxBread = 100;
    //     NBApprentices = atoi(argv[1]);
    //     scheduler_metric = FASTLEARNERS;
    //     if (NBApprentices < 1) {
    //         printf("Please input a positive number for the # Apprentices as first argument\n");
    //     	return;
    // 	}
    // } else if (argc == 3) {// 2 argument given = # chairs # maxBreads
    // 	maxBread = atoi(argv[2]);
    //     NBApprentices = atoi(argv[1]);
    //     if (NBApprentices < 1 || maxBread < 1) {
    //         printf("Please input a positive number for the # Apprentices as first argument\nand for the maximum amount of breads to be made as second arg\n");
    //         return;
    //     }
    // } else { //Default values
    //     NBApprentices = 30;
    //     maxBread = 100;
    //     scheduler_metric = ARRIVALORDER;
	// 	NBIngredients = 3;

	// 	//TODO get scenario
	// }

	NBApprentices = nbAppr;
	maxBread = maxB;
	NBIngredients = nbIngr;
	// ingredientNames = ingNames;
	scheduler_metric = metric;
	SCENARIO = scen;

	for (int i = 0; i < nbIngr; i++){
		// const char *bla = "Salt";
		// registerIngredient(ingNames[i], 50);
	}

	
    
    interested_array = malloc(NBApprentices*sizeof(timeType));
    threadIndexes = malloc(NBApprentices*sizeof(pthread_t));
    mutA = malloc(NBApprentices*sizeof(pthread_mutex_t));
    semA = malloc(NBApprentices*sizeof(sem_t));

    /* INITIALIZE MUTEX AND CONDITION VARIABLES */
    pthread_mutex_init(&mutex_inventory, NULL);
    sem_init(&bakers, 0, 0);
	sem_init(&semS, 0, 0);

    for(int i = 0; i < NBApprentices; i++){
        pthread_mutex_init(&mutA[i], NULL);
        sem_init(&semA[i], 0, 0);
        interested_array[i]=timeTypeMax;
    }

	/* CREATE THREADS */

	pthread_t bakert;
	pthread_create(&bakert, NULL, baker, (void *) 0);

    for (int i = 0; i < NBApprentices; i++){
        if(pthread_create(&threadIndexes[i], NULL, apprentice, (void *) i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Apprentice %d created!\n", i);
        }
    }

	// pthread_t shopper;
	// pthread_create(&shopper, NULL, shopper, NULL);

	int be = pthread_join(bakert, NULL);
	//printf("baker joined %d\n", be);

	//join threads so we see the printed output
	for (int i=0; i<NBApprentices; i++) { 
		pthread_join(threadIndexes[i], NULL);
		//printf("joined a thread\n");
	}

	return 0;

}

int main(int argc, char const *argv[]){
	char* ingr[] = {"Salt", "BP", "Water"};
	run(30, 100, 3, ingr, FAIRLEARNERS, 0);
	return 0;
}