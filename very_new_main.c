#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


#define N 10 // # of apprentices
#define MAX_A 20  // max # of apprentices
#define MAX_BREAD 100 // max # of breads to be made by the A.
 
pthread_mutex_t tMut = PTHREAD_MUTEX_INITIALIZER;  
pthread_cond_t cond[MAX_A]; // = PTHREAD_COND_INITIALIZER;
pthread_cond_t tCond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t bla = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t emut[MAX_A];//lock for each A
pthread_mutex_t fix = PTHREAD_MUTEX_INITIALIZER;
sem_t sp[MAX_A];


void *apprentice(void *j){
    int i = (int) j;
    int k=0;
    while (1){
    	
    	pthread_mutex_lock(&emut[i]);
    	
    	printf("Apprentice %d - %d\n", i, k); 

	// BREED
	
        printf("Apprentice %d's turn.\n", i);
		pthread_mutex_unlock(&emut[i]);
        pthread_cond_signal(&tCond);

        
        k++;


        printf("Apprentice %d is waiting for fix\n", i);
        sem_wait(&sp[i]);
        
        printf("Apprentice %d finished.\n", i);
        
    }
}


int main() {

    for (int i = 0; i < MAX_A; i++){
        pthread_cond_init(&cond[i], NULL);
    }
    for (int i = 0; i < MAX_A; i++){
    	pthread_mutex_init(&emut[i], NULL);
        pthread_mutex_lock(&emut[i]);
        sem_init(&sp[i], 0, 0);
    }

    pthread_t threads[MAX_A];

    

    for (int i = 0; i < N ; i++){
        if(pthread_create(&threads[i], NULL, apprentice, (void *)i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Thread %d created!\n", i);
        }
    }    

    int i = 0;
    while(1){

        printf("main waiting for A [%d]\n", i);
        pthread_cond_wait(&tCond, &emut[i]);//unlock
        printf("main woke up from A\n");

        printf("main waking A up\n");

        sem_post(&sp[i]);
        
        i = (i+1)%N;
    }
    return 0;
}









