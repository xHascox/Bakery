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

sem_t* semC;

sem_t semB;

void *baker(){
    
    while(TRUE) {

        sleep(1);

        sem_wait(&semB);

        if (bakeryOpen == FALSE)
            pthread_exit(NULL);
        

        sem_t* customer_semaphore = dequeue(chairs);

        sem_post(customer_semaphore);

        printf("Hi, that makes 2 Fr.\n");

    }
}

void *customer(void *id){
    
    int cid = (int) id;

    pthread_mutex_lock(&mutex_chairs);

    if (length(chairs) >= NBChairs) { // There are no free chairs
        printf("This place is overcrowded. I'm leaving!\n");
        pthread_mutex_unlock(&mutex_chairs);
        pthread_exit(NULL);

    } else { // There are free chairs

        enqueue(chairs, &semC[cid]); // Sit down on free chair

        sem_post(&semB); // Wake the baker

        pthread_mutex_unlock(&mutex_chairs);

        printf("Customer %d is waiting in a chair\n", cid);

        sem_wait(&semC[cid]); // Wait to be served

        printf("Thank you for selling me bread! Have a nice day!\n");

        pthread_exit(NULL); // Leave the bakery
    }
}

int main(int argc, char const *argv[]) {
    printf("started\n");
    
    if (argc == 1) {//Default valaues
        NBCustomers = 20;
        NBChairs = 10;
    } else if (argc == 2) {// one argument given = # chairs
        NBChairs = atoi(argv[1]);
        if (NBChairs < 1) {
            printf("Please input a positive number for the # chairs as first argument\n");
        }
    } else if (argc == 3) {
        NBChairs = atoi(argv[1]);
        NBCustomers = atoi(argv[2]);
        if (NBChairs < 1 || NBCustomers < 1) {
            printf("Please input a positive number for the # chairs as first argument\n");
            printf("Please input a positive number for the # customers as second argument\n");

        }
    }
  
    sem_init(&semB, 0, 0);

    chairs = init_queue();

    pthread_t threads[NBCustomers];
    
    semC = malloc(NBCustomers*sizeof(sem_t));
    
    //Customers
    for (int i=0; i < NBCustomers  ; i++) {
        //create customers thread

        sem_init(&semC[i], 0, 0);
        
        
        if(pthread_create(&threads[i], NULL, customer, (void *)i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Customer %d created!\n", i);
            // newApprentice(i);
        }

    }

    bakeryOpen = 1;
    pthread_t bakert;
    pthread_create(&bakert, NULL, baker, NULL);
    


    /* JOINING THREADS */
    for (int i = 0; i < NBCustomers; i++){
        pthread_join(threads[i], NULL);
    }
    printf("All customers joined!\n");

    bakeryOpen = 0;
    sem_post(&semB);
    pthread_join(bakert, NULL);
    printf("---closed---\n");

}
