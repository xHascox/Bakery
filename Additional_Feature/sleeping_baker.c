#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

int NBCustomers;
int NBChairs;

int bakeryOpen;

Queue* chairs;
pthread_mutex_t mutex_chairs;

sem_t* semC; // Customer semaphore :: dynamic array of sem_t

sem_t semB; // Baker semaphore

void *baker(){
    
    while(TRUE) {

        sem_wait(&semB);

        if (bakeryOpen == FALSE){ // Bakery closed --> exit
            pthread_exit(NULL);
        } else { // Bakery open --> Serve customers
            sleep(1); // Just to make the output readable
            sem_t* customer_semaphore = dequeue(chairs); 
            sem_post(customer_semaphore);
            printf("Hi, that makes 2 Fr.\n");
        }
    }
}

void *customer(void *id){
    
    int cid = (int) id;

    pthread_mutex_lock(&mutex_chairs);

    if (length(chairs) >= NBChairs) { // There are no free chairs
        printf("This place is overcrowded. I'm leaving! (Customer %d left).\n",cid);
        pthread_mutex_unlock(&mutex_chairs);

    } else { // There are free chairs
        enqueue(chairs, &semC[cid]);
        sem_post(&semB);
        pthread_mutex_unlock(&mutex_chairs);
        printf("Customer %d is waiting in a chair\n", cid);

        sem_wait(&semC[cid]); // Wait to be served

        printf("Thank you for selling me bread! Have a nice day!\n");
    }
    pthread_exit(NULL); // Leave the bakery
}

void runAddF(int nbcustomers, int nbchairs){

    printf("---start---\n");

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
    
    NBCustomers = nbcustomers;
    NBChairs = nbchairs;
    bakeryOpen = TRUE;

    chairs = init_queue();

    semC = malloc(NBCustomers*sizeof(sem_t));

    /* INITIALIZE MUTEX AND CONDITION VARIABLES */

    sem_init(&semB, 0, 0);

    for (int i=0; i < NBCustomers  ; i++)
        sem_init(&semC[i], 0, 0);

    /* CREATE THREADS */

    pthread_t threads[NBCustomers];
    
    for (int i=0; i < NBCustomers  ; i++) {
        if(pthread_create(&threads[i], NULL, customer, (void *)i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Customer %d created!\n", i);
        }
    }

    pthread_t bakert;
    pthread_create(&bakert, NULL, baker, NULL);
    

    /* JOINING THREADS */

    for (int i = 0; i < NBCustomers; i++){
        pthread_join(threads[i], NULL);
    }
    printf("All customers joined!\n");

    bakeryOpen = FALSE;
    sem_post(&semB);
    pthread_join(bakert, NULL);
    printf("---closed---\n");
}

/*
int main(int argc, char const *argv[]) {
    run(30,10);
}
*/
