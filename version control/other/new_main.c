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
        //pthread_cond_wait(&cond[i], &tMut);

        printf("Apprentice Before tMut %d\n", i);
        //pthread_mutex_lock(&tMut);

	// EAT AND MAKE BREAT AND LIVE
	
        printf("Apprentice %d's turn.\n", i);
		pthread_mutex_unlock(&emut[i]);
        pthread_cond_signal(&tCond);
        //pthread_mutex_unlock(&tMut);
        
        k++;
        //sleep(1);
        //pthread_cond_wait(&aCond, &fix);//unlock
        printf("Apprentice %d is waiting for fix\n", i);
        sem_wait(&sp[i]);
        //pthread_mutex_lock(&fix);
        //printf("Apprentice %d is waiting for cond\n", i);
        //pthread_cond_wait(&cond[i], &fix);
        //pthread_mutex_unlock(&fix);//prevent sthread from stealing emit[i] before main
        //pthread_mutex_lock(&fix);
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

    pthread_mutex_lock(&tMut);
    //pthread_mutex_lock(&fix);
    

    for (int i = 0; i < N ; i++){
        if(pthread_create(&threads[i], NULL, apprentice, (void *)i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Thread %d created!\n", i);
        }
    }    

    sleep(1); // Give threads time to initilize

    int i = 0;
    while(1){
        printf("Main's turn.\n");
        //pthread_mutex_unlock(&tMut);
        printf("main unlocked tmut\n");
        //pthread_mutex_unlock(&emut[i]);//unlock
        //pthread_cond_signal(&cond[i]);//unlock
        printf("main waiting for A [%d]\n", i);
        pthread_cond_wait(&tCond, &emut[i]);//unlock
        printf("main woke up from A\n");
        //pthread_mutex_lock(&emut[i]);//lock
        printf("main got emut\n");
        //pthread_mutex_lock(&tMut);
        
        printf("main waking A up\n");
        //pthread_mutex_unlock(&tMut);
        //pthread_cond_signal(&cond[i]);
        sem_post(&sp[i]);
        
        printf("main finished\n");
        i = (i+1)%N;
    }
    return 0;
}









