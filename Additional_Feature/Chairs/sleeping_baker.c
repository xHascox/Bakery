#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

int NbCustomers;
int N;// # chairs

int bakeryOpen;

//Chairs (Queue of customers) and the corresponding mutex
Queue* chairs;
pthread_mutex_t mutex_chairs;

sem_t* customer_semaphore;//array of semaphores

//baker's semaphore
sem_t baker_semaphore;

//baker
void *baker(){
    
    while(TRUE) {
        if (!bakeryOpen) {
            pthread_exit(NULL);
        }
        sem_wait(&baker_semaphore);
        if (!bakeryOpen) {
            pthread_exit(NULL);
        }

        //dequeue
        sem_t* customer = dequeue(chairs);


	printf("waking up %d\n", &customer);
        //wake up dequeued customer
        sem_post(&customer);


        //sell bread / friendy smalltalk
        printf("That makes 2 Fr for that delicious fribourgeois bread\n");
        

    }
}



void *customer(void *id){
    
    int cid = (int )id;
    pthread_mutex_lock(&mutex_chairs);

    //if Q full: kill
    if (length(chairs)>= N) {
        printf("I'm leaving, 0 star, overcrowded\n");
        pthread_mutex_unlock(&mutex_chairs);
        pthread_exit(NULL);
    } 
    else {

        //sit down on free chair
        enqueue(chairs, &customer_semaphore[cid]);

        //wake Baker up
        sem_post(&baker_semaphore);

        pthread_mutex_unlock(&mutex_chairs);

        printf("I %d waiting in a chair\n", cid);

        //wait to be served
        sem_wait(&customer_semaphore[cid]);

        printf("thanks for selling me bread\n");

        pthread_exit(NULL);
    }
}



int main(int argc, char const *argv[]) {
    printf("started\n");
    
    if (argc == 1) {//Default valaues
        NbCustomers = 30;
        N=10;
    } else if (argc == 2) {// one argument given = # chairs
        N = atoi(argv[1]);
        if (N < 1) {
            printf("Please input a positive number for the # chairs as first argument\n");
        }
    } else if (argc == 3) {
        N = atoi(argv[1]);
        NbCustomers = atoi(argv[2]);
        if (N < 1 || NbCustomers < 1) {
            printf("Please input a positive number for the # chairs as first argument\n");
            printf("Please input a positive number for the # customers as second argument\n");

        }
    }
  
    sem_init(&baker_semaphore, 0, 0);

    chairs = init_queue();

    pthread_t threads[NbCustomers];
    
    //sem_t customer_s[NbCustomers];
    customer_semaphore = malloc(NbCustomers*sizeof(sem_t));
    
    //Customers
    for (int i=0; i < NbCustomers  ; i++) {
        //create customers thread

        sem_init(&customer_semaphore[i], 0, 0);
        
        
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
    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    printf("All customers joined!\n");

    bakeryOpen = 0;
    sem_post(&baker_semaphore);
    pthread_join(bakert, NULL);
    printf("---closed---\n");

}
