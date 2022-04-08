#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>



#define N 3


int flour = INT_MAX;
int oil;
int bp; //baking powder


void *apprentice(void *j){
    int i = (int) j;

    printf("Thread %d did something!\n",j);




    pthread_exit((void *)i);
}




int main() {

    

    /* CREATING THREADS */
    pthread_t threads[N];

    for (int i = 0; i < N ; i++){
        if(pthread_create(&threads[i], NULL, apprentice, (void *)i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Thread %d created!\n", i);
        }

    }






    /* JOINING THREADS */

    for (int i = 0; i < N; i++){
        int val;
        pthread_join(threads[i], (void **)&val);
        printf("Thread is %d \n", val);
    }
    





    return 0;
}