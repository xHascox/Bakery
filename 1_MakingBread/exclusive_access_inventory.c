#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define GRANTED 0

int NBApprentices; // Number of apprentices :: int
int *threadIndexes; // Array keeping track of apprentice IDs :: Array of int
int *interested_array; // Array of size NBApprentices where apprentices can anounce interest in accessing the inventory :: Array of int
// Node *inventory; // Inventory :: Dynamic array of linked lists
pthread_mutex_t mutex_inventory; // Mutex to ensure mutual exclusive access to inventory :: pthread_sem_t
pthread_mutex_t *mutA; // Mutexes and condition variable (1 for each apprentice) to wake it up once they're allow to access the inventory
pthread_cond_t *condA;
pthread_cond_t *contT // Condition variable to wake up teacher :: pthread_cond_t

void access_inventory(int i){
    printf("Apprentic %d accesses the inventory.\n",i);
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

    int i = (int) j; // Apprentice ID

    while(1){
        printf("Apprentice %d wants to access the inventory.\n",i);

        int access = pthread_mutex_trylock(&mutex_inventory);
        if (access == GRANTED){
            access_inventory(i);
            pthread_mutex_unlock(&mutex_inventory);
        } else {
            int metric = 1; // TODO Change to desired metric
            interested_array[i] = metric; // Announce interest
            pthread_mutex_lock(&mutA[i]); // Wait until it's my turn

            pthread_mutex_lock(&mutex_inventory);
            access_inventory(i);
            pthread_mutex_unlock(&mutex_inventory);
        }

        printf("Apprentice %d just baked some bread.\n",i);
    }
}



int main(int argc, char const *argv[]){

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
    if (argc == 1) {
        NBApprentices = 10;
    }

    interested_array = malloc(NBApprentices*sizeof(int));
    threadIndexes = malloc(NBApprentices*sizeof(int));
    condA = malloc(NBApprentices*sizeof(pthread_cond_t));
    mutA = malloc(NBApprentices*sizeof(pthread_mutex_t));


    /* INITIALIZE MUTEX AND CONDITION VARIABLES */
    mutex_init(&mutex_inventory, NULL);
    pthread_cond_init(&condT, NULL);

    for(int i = 0; i < NBApprentices; i++){
        pthread_mutex_init(&mutA[i], NULL);
        pthread_cond_init(&condA[i], NULL);
    }

    /* CREATE THREADS REPRESENTING APPRENTICES */
    for (int i = 0; i < NBApprentices; i++){
        if(pthread_create(&threadIndexes[i], NULL, apprentice, (void *) i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Apprentice %d created!\n", i);
        }
    }

    return 0;
}