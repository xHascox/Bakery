#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define GRANTED 0

int NBApprentices; // Number of apprentices :: int
int *threadIndexes; // Array keeping track of apprentice IDs :: Array of int
int *interested_array; // Array of size NBApprentices where apprentices can anounce interest in accessing the inventory :: Array of int
// Node *inventory; // Inventory :: Dynamic array of linked lists
pthread_sem_t sem_inventory; // Semaphore to ensure mutual exclusive access to inventory :: pthread_sem_t
pthread_cond_t *condA;  // Condition variables wake them once they're allowed to access the inventory :: Array of condition variables

void access_inventory(int i){
    printf("Apprentic %d accesses the inventory.\n",i);
}

void *apprentice(void *j){
    /*
    - Say hello
    - Try access inventory:
        - check mutex on the resource you desire using peek
            - if +: Go and get the resource and then free the mutex
            - if -: Insert your timestamp in interested array and sleep on your semaphore
                    As soon as your woken up by teacher, you get the mutex.
    - Bake bread
    - Repeat
    */

    int i = (int) j; // Apprentice ID

    while(1){
        printf("Apprentice %d wants to access the inventory.\n",i);
        int access = sem_trywait(&sem_inventory);
        if (access == GRANTED){
            access_inventory(i);
            sem_(&sem_inventory);
        } else {
            int metric = 1; // TODO Change to desired metric
            interested_array[i] = metric; // Announce interest
            sem_wait();
        }
        printf("Apprentice %d just baked some bread.\n",i);
    }
}



int main(int argc, char const *argv[]){

    if (argc == 1) { //Default valaues
        NBApprentices = 10;
    }

    sem_init(&sem_inventory, 0, 0);

    // Allocate memory for dynamic array
    interested_array = malloc(NBApprentices*sizeof(int));
    threadIndexes = malloc(NBApprentices*sizeof(int));
    condA = malloc(NBApprentices*sizeof(pthread_cond_t));

    // Creating threads representing apprentices
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