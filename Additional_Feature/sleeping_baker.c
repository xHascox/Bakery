#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

#define N 10
#define NbCustomers 30

//Chairs (Queue of customers) and the corresponding mutex
Queue* chairs = init_queue();
pthread_mutex_t mutex_chairs;

//baker's semaphore
sem_t baker_semaphore;

//baker
void *baker(void *j){
    while(TRUE) {
        sem_wait(&baker_semaphore);

        //dequeue
        sem_t customer = dequeue(chairs);



        //wake up dequeued customer
        sem_post(&customer);


        //sell bread / friendy smalltalk
        printf("That makes 2 Fr for that delicious fribourgeois bread\n");
        

    }

}



void *customer(){
    
    pthread_mutex_lock(&mutex_chairs);

    //if Q full: kill
    if (length(chairs)>= N) {
        printf("I'm leaving, 0 star, overcrowded\n");
        pthread_exit();
    } 
    else {
        sem_t customer_semaphore;
        sem_init(&customer_semaphore, 0, 0);

        //sit down on free chair
        enqueue(chairs, customer_semaphore);

        //wake Baker up
        sem_post(&baker_semaphore);

        //wait to be served
        sem_wait(&customer_semaphore);

        printf("thanks for selling me bread\n");

        pthread_exit();
    }
        

       

}



int main() {
    sem_init(&baker_semaphore, 0, 0);


    pthread_t threads[NbCustomers];

    //Customers
    for (int i=0; i< NbCustomers  ; i++) {
        //create customers thread

        
        
        if(pthread_create(&threads[i], NULL, customer, NULL)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Customer %d created!\n", i);
            // newApprentice(i);
        }

    }


    /* JOINING THREADS */
    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    printf("All threads joined!\n");

}