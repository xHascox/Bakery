#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>

#include "Inventory_BinTree.h" // Include inventory datastructure

// Different strategies to "schedule" apprentices to enter the inventory
int scheduler_metric; 
#define FAIRLEARNERS 0 // Schedule the apprentice with the smallest number of breads made
#define FASTLEARNERS 1 // Schedule the apprentice with the largest number of breads made
#define ARRIVALORDER 2 // Schedule the apprentice that arrived first (using timestamps)
#define PRELEARNERS 3 // Schedule according to a predefined order

// Different scenarios for testing
int scenario;
#define SCENARIO1 1 // Two apprentices add the same item to the inventory at the same time
#define SCENARIO2 2 // Two apprentices get the same item from the inventory at the same time
#define SCENARIO3 3 // One apprentices gets an item while, at the same time, another apprentice adds the same item

// Timestamps
#define timeType unsigned long
#define timeTypeMax ULONG_MAX
struct timeval tvbase, tvnow;

// Global variables
int breads = 0; // Number of breads made in total :: int
int maxBread; // Number of breads were going to make today :: int
int NBApprentices; // Number of apprentices :: int
pthread_t *threadIndexes; // Array keeping track of apprentice IDs :: Array of int
timeType *interested_array; // Array of size NBApprentices where apprentices can anounce interest in accessing the inventory :: Array of int
pthread_mutex_t mutex_inventory; // Mutex to ensure mutual exclusive access to inventory :: pthread_mutex_t
sem_t *semA; // Array of size NBApprentices containing a semaphore per apprentice to wake them up once they're allowed to access the inventory :: Array of pthread_sem_t
sem_t semB; // Semaphore to wake up baker :: sem_t 
sem_t semS; // Semaphore to wake up shopper :: sem_t
int NBIngredients; 
char **ingredientNames;

// Functions
void *baker(void *j);
void *shopper();
void *apprentice(void *j);
void access_inventory(int i);


void *baker(void *j){
	int scenario2alt=0;
	int scenario2j;
	
	while (breads < maxBread) {
	
		timeType min = timeTypeMax;
		int j = -1;//the next A to be allowed into Inv
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
			if (scenario == SCENARIO2 && scenario2alt == 0) {
				
				scenario2alt = 1;
				scenario2j = j;
				interested_array[j]=timeTypeMax;
				continue;//dont sleep for one loop

			} else if (scenario == SCENARIO2) {
				scenario2alt = 0; //to sleep after waking up 2 apprentices
				//wakre up both A
				interested_array[j]=timeTypeMax;
				printf("Baker wakes up %d and %d simultaneously\n", j, scenario2j);
				sem_post(&semA[j]);
				sem_post(&semA[scenario2j]);
				
				//baker sleep until that one is finished
				//printf("baker sleeping");
				sem_wait(&semB);
				sem_wait(&semB);
				continue;
			}

			//wakre up A
			interested_array[j]=timeTypeMax;
			printf("Baker wakes up %d with metric: %lu\n", j, min);
			sem_post(&semA[j]);
			
			//baker sleep until that one is finished
			//printf("baker sleeping");
			sem_wait(&semB);	

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
	    	printf("     Apprentice %d made bread #%d (their %dth bread)\n",i, breads, abread);
	    	pthread_exit(NULL);
	    }
	    breads++;
	    abread++;
	    printf("     Apprentice %d made bread #%d (their %dth bread)\n",i, breads, abread);
	    pthread_mutex_unlock(&mutex_inventory);
	    
	    //tell baker you are out again
	    sem_post(&semB);
        
		sleep(rand()%3+1);
        
        
    }
    printf("     Apprentice %d made %d breads today\n", i, abread);
}

void access_inventory(int i){
	
	printf("     Apprentice %d accesses the inventory\n",i);
	printf("     Apprentice %d takes ",i);

	for(int j = 0; j < NBIngredients; j++){
		char* ingredient = ingredientNames[j];
		for(int k = 0; ingredient[k] != '\0'; k++){
			printf("%c", ingredient[k]);
		}
		if(j < NBIngredients - 2){
			printf(", ");
		}else if(j < NBIngredients - 1){
			printf(" and ");
		} else {
			printf(" ");
		}
		takeIngredient(ingredient, 1);
	}
	printf("from the inventory and leaves\n");
}

int run (int nbAppr, int maxB, int nbIngr, char* ingNames[], int metric, int scen){
	srand(time(NULL));
	gettimeofday(&tvbase, NULL);

    /* INITIALIZE VARIABLES BASED ON USER INPUT */

	NBApprentices = nbAppr;
	maxBread = maxB;
	NBIngredients = nbIngr;
	scheduler_metric = metric;
	scenario = scen;

	ingredientNames = malloc(nbIngr * sizeof(char*));
	for (int i = 0; i < nbIngr; i++){
		registerIngredient(ingNames[i], 50); // Register the ingredients and add 50 units per ingredient
    	ingredientNames[i] = malloc((32 + 1) * sizeof(char)); // Max string length is 32 chars
		strcpy(ingredientNames[i], ingNames[i]);
	}

    interested_array = malloc(NBApprentices*sizeof(timeType));
    threadIndexes = malloc(NBApprentices*sizeof(pthread_t));
    semA = malloc(NBApprentices*sizeof(sem_t));

    /* INITIALIZE MUTEX AND CONDITION VARIABLES */

    pthread_mutex_init(&mutex_inventory, NULL);
    sem_init(&semB, 0, 0);
	sem_init(&semS, 0, 0);

    for(int i = 0; i < NBApprentices; i++){
        sem_init(&semA[i], 0, 0);
        interested_array[i]=timeTypeMax;
    }

	/* CREATE THREADS */

	// Baker
	pthread_t bakert;
	pthread_create(&bakert, NULL, baker, (void *) 0);

	// Apprentices
    for (int i = 0; i < NBApprentices; i++){
        if(pthread_create(&threadIndexes[i], NULL, apprentice, (void *) i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Apprentice %d created!\n", i);
        }
    }

	// Shopper
	// pthread_t shopper;
	// pthread_create(&shopper, NULL, shopper, NULL);

	/* CLEANUP */

	// Join threads
	pthread_join(bakert, NULL);

	for (int i=0; i<NBApprentices; i++) { 
		pthread_join(threadIndexes[i], NULL);
	}

	// Free memory
	free(interested_array);
	free(threadIndexes);
	free(semA);

	return 0;

}

int main(int argc, char const *argv[]){
	char* ingr[] = {"Salt", "BP", "Water"};
	run(30, 100, 3, ingr, FAIRLEARNERS, 0);
	return 0;
}
