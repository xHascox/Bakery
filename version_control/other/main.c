#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "Inventory.h"


#define N 5 // # of apprentices
#define MAX_A 20  // max # of apprentices
#define MAX_BREAD 1000 // max # of breads to be made by the A.

#define TRUE 1
#define FALSE 0

/* CONDITION VARIABLES, MUTEXES AND SEMAPHORES */
pthread_mutex_t mutA[MAX_A];   
pthread_cond_t condA[MAX_A]; 
pthread_cond_t condT = PTHREAD_COND_INITIALIZER;
sem_t sp[MAX_A];

/* INVETORY */
void RegisterIngredients() {
    RegisterIngredient("flour", INT_MAX);
    RegisterIngredient("oil", INT_MAX);
    RegisterIngredient("bp", INT_MAX);
    RegisterIngredient("sugar", INT_MAX);
    RegisterIngredient("salt", INT_MAX);
}
int breads = 0;     // # of breads made

/* FOR COMMUNICATION: APPRENTICE - TEACHER */
int finished[MAX_A];

/* APPRENTICE FUNCTION */
void *apprentice(void *j){
    int i = *(int*) j;

    while (1){

        pthread_mutex_lock(&mutA[i]);

        if (breads == MAX_BREAD){ // Enough bread? If so, exit.
            pthread_mutex_unlock(&mutA[i]);
            printf("Killing %d\n", i);
            finished[i] = TRUE;
            pthread_cond_signal(&condT);
            pthread_exit(NULL);
        }

        printf("Entering Inventory: i = %d\n", i); 
        TakeIngredient("flour");
        TakeIngredient("oil");
        TakeIngredient("bp");
        TakeIngredient("sugar");
        TakeIngredient("salt");
            
        breads += 1;
        printf("Apprentice %d just made some bread.\n",i);

        pthread_mutex_unlock(&mutA[i]);
        pthread_cond_signal(&condT);

        sem_wait(&sp[i]);        
    }
}

int main() {

    /* INITIALIZING CONDITION AND MUTEX VARIABLE ARRAYS */
    for (int i = 0; i < MAX_A; i++){
        pthread_cond_init(&condA[i], NULL); // Initilaize a condition variable for each apprentice.
        pthread_mutex_init(&mutA[i], NULL); // Initilaize a mutex for each apprentice.
        pthread_mutex_lock(&mutA[i]);       // Also lock mutex immediately   
        sem_init(&sp[i], 0, 0);
        finished[i] = FALSE;                
    }
    

    /* CREATING THREADS */
    pthread_t threads[MAX_A];
    int threadIndexes[N];   // store the thread-id in a place where it is alive during the lifespan of the thread
    for (int i = 0; i < N ; i++){
        threadIndexes[i] = i;
        if(pthread_create(&threads[i], NULL, apprentice, (void *) &threadIndexes[i])){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Thread %d created!\n", i);
            // newApprentice(i);
        }
    }    

    /* BAKING BREADS */
    int i = 0;
    while(1){

        pthread_cond_wait(&condT,&mutA[i]);

        sem_post(&sp[i]);

        i = (i+1)%N;
        printf("Current amount of bread: %d\n", breads);

        if (breads == MAX_BREAD){
            int k = 0;
            for (int i = 0; i < N; i++){
                k += finished[i];
            }
            if (k == N){
                break;
            }
        }
    }

    /* JOINING THREADS */
    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    printf("All threads joined!\n");
    

    return 0;
}