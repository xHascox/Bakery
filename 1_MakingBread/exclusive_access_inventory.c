#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include "exclusive_access_inventory.h"
#include "Recipe_Book.h"
#include "Inventory_BinTree.h"

#define FALSE 0
#define TRUE 1

// Different strategies to "schedule" apprentices to enter the inventory
int scheduler_metric; 
#define FAIRLEARNERS 0 // Schedule the apprentice with the smallest number of breads made
#define FASTLEARNERS 1 // Schedule the apprentice with the largest number of breads made
#define ARRIVALORDER 2 // Schedule the apprentice that arrived first (using timestamps)
#define PRELEARNERS 3 // Schedule according to a predefined order

// Different scenarios for testing
int scenario;
#define SCENARIO2 2 // Two apprentices get the same item from the inventory at the same time

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
sem_t semEmpty; // Condition variable for apprentice that has to wait for shopper :: sem_t
int* NBIngredients; // Number of ingredients per bread type :: Array of int
char ***ingredientNames; // Ingredient names per bread type :: Array of arrays of strings
char **breadNames; // Names of bread types :: Array of strings
int NBBreadtypes; // Number of bread types :: int
int restockToVal; // Initial number of units per ingredient and restock target :: int

// Functions
void *baker(void *j);
void *shopper();
void *apprentice(void *j);
void access_inventory(int i);

/**
 * @brief The 'baker' is a thread which handles the apprentices's access to the inventory.
 * 
 * 	TODO: ADD MORE DESCRIPTION
 * 
 * @param j Specifying pointer some value identifying the baker
 * @return void* 
 */
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

			// Wake up A
			interested_array[j]=timeTypeMax;
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
	sem_post(&semS);
	pthread_exit(&ret);
}


/**
 * @brief The 'shopper' is a thread which handles the restocking of the ingredients. \n
 * This thread is activated when an apprentice tries to take ingredients from the inventory but the amount of ingredients present (stock) is not sufficient. \n
 * It then restocks the ingredients to the restockTo-value. Additionally, this thread locks the inventory befre accessing it.
 * 
 * @return void* 
 */
void *shopper_func(){
	while(1){
		sem_wait(&semS);
		if(breads >= maxBread){
			pthread_exit(NULL);
		}
		printf("\nAlright, will restock.\n");
		pthread_mutex_lock(&mutex_inventory);
		restockIngredients();
		printInvTree();
		pthread_mutex_unlock(&mutex_inventory);
		printf("________________________________\nInventory succesfully restocked.\n\n");
		sem_post(&semEmpty);
	}
}

/**
 * @brief The 'apprentice' is a thread which is accessing the inventory, retrieving the necessary ingredients and bakes bread. \n
 * First, the chosen startegy for 'learnign to make bread' is applied. Then, it waits for the baker to post this apprentice's semaphore to wake it up. \n
 * If is is woken up, the inventory mutex is locked to gain sole access to it. After the inventory access and bread baking, the stopping condition, the amount of breads baked, is checked.
 * 
 * @param j Specifying pointer to some value identifying the apprentice
 * @return void* 
 */
void *apprentice(void *j){

    int i = *(int*) j; // Apprentice ID
    int abread = 0;
    
	timeType metric;
    while(breads < maxBread){
        //printf("Apprentice %d wants to access the inventory.\n",i);
		
		gettimeofday(&tvnow, NULL);
	
	    if (scheduler_metric == ARRIVALORDER) {
	    	metric = (tvnow.tv_sec - tvbase.tv_sec)*1000000 + (tvnow.tv_usec - tvbase.tv_usec);
	    	//printf("%lu = %lu  . %lu\n", metric, tvnow.tv_sec, tvnow.tv_usec);  
	    } else if (scheduler_metric == FASTLEARNERS) {
	    	metric = timeTypeMax - abread - 1;
			//printf("%d metric: %lu\n", i, metric);
	    } else if (scheduler_metric == FAIRLEARNERS) {
	    	metric = abread;
	    } else if (scheduler_metric == PRELEARNERS) {
	    	metric = i;
	    } 
	    
	    
	    interested_array[i] = metric; // Announce interest
	    
	    sem_wait(&semA[i]); // Wait until its my turn
		printf("Apprentice %d woke up:\n", i);

	    pthread_mutex_lock(&mutex_inventory);
	    access_inventory(i);
	    if (breads>=maxBread) { // Bakery closed for the day
	    	pthread_mutex_unlock(&mutex_inventory);	
	    	printf("     Apprentice %d made bread #%d (their %dth bread)\n",i, breads, abread);
	    	pthread_exit(NULL);
	    } else { // Bakery still open
			breads++;
			abread++;
			printf("     Apprentice %d made bread #%d (their %dth bread)\n",i, breads, abread);
			pthread_mutex_unlock(&mutex_inventory);
			
			sem_post(&semB); // Tell the baker I'm out again
			
			sleep(rand()%3+1);
		}        
    }
    printf("     Apprentice %d made %d breads today\n", i, abread);
	pthread_exit(NULL);
}

/**
 * @brief This function is called when an apprentice want to access the inventory. Here, a bread type is chosen \n
 *  and this type's ingredients array and the amount of different ingredients fetched. \n
 *  Then, for each ingredient required for this bread type, a unit is removed from the inventory. \n
 *  When retrieving it is checked whether or not there are enough ingredients left. If no, the shopper is activated.
 * 
 * @param i int specifying entering apprentice
 */
void access_inventory(int i){
	
	printf("     Apprentice %d accesses the inventory\n",i);
	
	/* Choose which bread to make */
	char* breadName = breadNames[rand()%NBBreadtypes/* +1 ??*/];
	char** ingredients = getIngredArray(breadName);
	int ingredients_len = getNbIngredOfBreadType(breadName);

	printf("     Apprentice %d will make a %s\n",i, breadName);
	printf("     For that they take: ");

	/* Taking ingredients and handling unsufficient stock */
	for(int j = 0; j < ingredients_len; j++){
		char *ingredient = ingredients[j];
		int in_stock = takeIngredient(ingredient, 1);
		if(in_stock){
			printf("%s ",ingredient);
		} else {
			printf("\n     Unfortunately, there is no more %s in stock. Somebody needs to go shopping.\n", ingredient);

			pthread_mutex_unlock(&mutex_inventory);
			sem_post(&semS);
			sem_wait(&semEmpty);
			pthread_mutex_lock(&mutex_inventory);

			printf("    Thanks for restocking!\n");
			takeIngredient(ingredient, 1);
			printf("    %s ",ingredient);
		}
	}
	printf("\n");

	printf("     from the inventory and leave\n");
}


/**
 * @brief This is the main run function of 'learning to make bread' being passed all the necessary arguments. \n
 * First the function arguments are stored into local variables. Then, the recipe book and the invcentory are created. \n
 * Thirdly, the mutex, semaphore and index array for the apprentices are malloc'ed and initialized. \n
 * After that, the threads (baker, shopper, and the apprentices) are created  ans start their operation. \n
 * Lastly, after having baked enough breads, all the threads are joined together and some memory is freed.
 * 
 * @param nbAppr Number of apprentices
 * @param maxB The total amount of bread to be baked
 * @param nbBT Number of bread types
 * @param breadNamesArr Array for each bread type's name
 * @param nbIngrArr An array of int specifying the amount of ingredients each bread type needs; the index corresponds to the different bread types
 * @param ingNames An array with size equal to the number of bread types, pointing to the amount of ingredients (strings) each bread type has.
 * @param stonks Amount of initial stock and 'restockTo'-value
 * @param metric Chosing scheduling algorithm for 'learning to make bread'
 * @param scen The second scenario an be acivated by entering the specific value (2)
 */
void runMakingBread (int nbAppr, int maxB, int nbBT, char** breadNamesArr, int* nbIngrArr, char*** ingNames, int stonks, int metric, int scen) {
	
	printf("Beginning\n");

	srand(time(NULL));
	gettimeofday(&tvbase, NULL);

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
	NBApprentices = nbAppr;
	maxBread = maxB;
	NBIngredients = nbIngrArr;
	ingredientNames = ingNames;
	restockToVal = stonks;
	NBBreadtypes = nbBT;
	breadNames = breadNamesArr;
	scheduler_metric = metric;
	scenario = scen;

	
	printf("Before Recipe Book\n");

	/* RECIPE BOOK CREATION */
	for (int i = 0; i < NBBreadtypes; i++){
		registerBreadType(breadNames[i], NBIngredients[i], ingredientNames[i]);
	}

	printf("Before IngredInv\n");
	
	/* INGREDIENTS INVENTORY CREATION */
	for (int i = 0; i < NBBreadtypes; i++){
		for (int j = 0; j < NBIngredients[i]; j++){
			registerIngredient(ingredientNames[i][j], restockToVal);
		}
	}


	/* -----------------DEBUG--------------------- */
	//*
	printf("\n\n");
	printf("_____________________________________________");
	printRecipeBook();

	printf("\n\n");
	printf("_____________________________________________");
	printInvTree();
	//*/
	/* ------------------------------------------- */


	
    interested_array = malloc(NBApprentices*sizeof(timeType));
    threadIndexes = malloc(NBApprentices*sizeof(pthread_t));
    semA = malloc(NBApprentices*sizeof(sem_t));


    /* INITIALIZE MUTEX AND CONDITION VARIABLES */

    pthread_mutex_init(&mutex_inventory, NULL);
    sem_init(&semB, 0, 0);
	sem_init(&semS, 0, 0);
	sem_init(&semEmpty, 0, 0);

    for(int i = 0; i < NBApprentices; i++){
        sem_init(&semA[i], 0, 0);
        interested_array[i]=timeTypeMax;
    }


	/* CREATE THREADS */

	// Baker
	pthread_t bakert;
	pthread_create(&bakert, NULL, baker, (void *) 0);

	// Apprentices
	int iVals[nbAppr];
    for (int i = 0; i < NBApprentices; i++){
		iVals[i] = i;
        if(pthread_create(&threadIndexes[i], NULL, apprentice, (void *) &iVals[i])){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Apprentice %d created!\n", i);
        }
    }

	// Shopper
	pthread_t shopper;
	pthread_create(&shopper, NULL, shopper_func, NULL);


	/* CLEANUP */

	// Join threads
	pthread_join(bakert, NULL);
	pthread_join(shopper, NULL);
	
	for (int i=0; i<NBApprentices; i++) { 
		pthread_join(threadIndexes[i], NULL);
	}

	// Free memory
	free(interested_array);
	free(threadIndexes);
	free(semA);


}

/*
int main(int argc, char const *argv[]){
	
	int nbBT = 2;
	char* ingr01[] = {"Salt", "BP", "Water"};
	char* ingr02[] = {"Shit","Kek"};
	char** ingr[] = {ingr01, ingr02};
	int nbI[] = {3,2};
	char* BT[] = {"HHH", "KKK"};
	
	int toTheMoon = 10;
	
	

	int maxLen = 32;
    char*** IArr;
    int nbBTy = 2;
    int nbIng01 = 2;
    int nbIng02 = 3;
    char** btName;
	int* nbIn;
	int toTheMooon = 10;

	nbIn = (int*)malloc(nbBTy*sizeof(int));
	nbIn[0] = nbIng01;
	nbIn[1] = nbIng02;

    btName = malloc(nbBTy*sizeof(char*));
    btName[0] = malloc(maxLen*sizeof(char));
    btName[1] = malloc(maxLen*sizeof(char));

    strcpy(btName[0],"Bread01");
    strcpy(btName[1],"Bread02");


    IArr = malloc(nbBTy*sizeof(char*));
    IArr[0] = malloc(nbIng01*sizeof(char*));
    IArr[0][0] = malloc(maxLen*sizeof(char));
    IArr[0][1] = malloc(maxLen*sizeof(char));
    IArr[1] = malloc(nbIng02*sizeof(char*));
    IArr[1][0] = malloc(maxLen*sizeof(char));
    IArr[1][1] = malloc(maxLen*sizeof(char));
    IArr[1][2] = malloc(maxLen*sizeof(char));

    strcpy(IArr[0][0],"flour");
    strcpy(IArr[0][1],"oil");
    strcpy(IArr[1][0],"oil");
    strcpy(IArr[1][1],"bp");
    strcpy(IArr[1][2],"flour");

	runMakingBread(30, 100, nbIn, IArr, toTheMooon, nbBTy, btName, FAIRLEARNERS, 0);
	return 0;
}
*/
