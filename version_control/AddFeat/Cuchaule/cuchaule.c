#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>




#define STEPS 8

#define TRUE 1
#define FALSE 0

/* CONDITION VARIABLES, MUTEXES AND SEMAPHORES */
pthread_mutex_t mutA[STEPS];   
pthread_cond_t condA[STEPS]; 
pthread_cond_t condT = PTHREAD_COND_INITIALIZER;
sem_t sp[STEPS];


/* TABLE */ 
int hasIngredients;

/* INVENTORY */
int flour = INT_MAX;
int milk = INT_MAX;
int butter = INT_MAX;
int sugar = INT_MAX;
int salt = INT_MAX;
int safran = INT_MAX;
int yeast = INT_MAX;
int egg = INT_MAX;

int nbOfCuchaule = 0;


void fetchIngredients(){

    flour -= 1000;
    milk -= 500;
    butter -= 100;
    sugar -= 120;
    salt -= 1;
    safran -= 1;
    yeast -= 20;
    egg -= 1;

    hasIngredients = 1;

    return;
}


/* APPRENTICE FUNCTION */
void *apprentice(void *j){
    int i = *(int*) j;

    while (TRUE){

        pthread_mutex_lock(&mutA[i]);

        switch (i)
        {
        case 0:
            printf("Doing step %d of recipe: Dissolve yeast and sugar in milk.\n", i);
            break;
        case 1:
            printf("Doing step %d of recipe: Put flour into bowl.\n", i);
            break;
        case 2:
            printf("Doing step %d of recipe: Put butter, milk, safran and salt into bowl.\n", i);
            break;
        case 3:
            printf("Doing step %d of recipe: Mix everything and knead the dough thoroughly.\n", i);
            break;
        case 4:
            printf("Doing step %d of recipe: Let the dough rise for 2 houres.\n", i);
            break;
        case 5:
            printf("Doing step %d of recipe: Form the loaf(s).\n", i);
            break;
        case 6:
            printf("Doing step %d of recipe: Coat loaf(s) with egg yolk and safran.\n", i);
            break;
        case 7:
            printf("Doing step %d of recipe: Cut an 'X' into the bread and bake it for 40 minutes.\n", i);
            break;
        
        default:
            printf("The step %d did not go well.  :( \n", i);
            exit(1);
            break;
        }
       

        pthread_mutex_unlock(&mutA[i]);
        pthread_cond_signal(&condT);

        sem_wait(&sp[i]);

    }
}




void teacher(){

    pthread_t threads[STEPS];
    int threadIndexes[STEPS];
    for (int i = 0; i < STEPS ; i++){
        threadIndexes[i] = i;
        if(pthread_create(&threads[i], NULL, apprentice, (void *) &threadIndexes[i])){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Thread %d created!\n", i);
        }
    }    


    int i = 0;
    while (TRUE){

        pthread_cond_wait(&condT,&mutA[i]);

        // PUT INGREDIENTS ONTO TABLE
        fetchIngredients();

        // Call every assistant
        sem_post(&sp[i]);

        i = (i+1)%STEPS;
        printf("Number of Cuchaule: %d\n", nbOfCuchaule);

    }
    

    /* JOINING THREADS */ /*
    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    printf("All threads joined!\n");
    */
    
    return;
}




int main(/*int argc, char const *argv[]*/){

    /* INITIALIZING CONDITION AND MUTEX VARIABLE ARRAYS */
    for (int i = 0; i < STEPS; i++){
        pthread_cond_init(&condA[i], NULL); // Initilaize a condition variable for each apprentice.
        pthread_mutex_init(&mutA[i], NULL); // Initilaize a mutex for each apprentice.
        pthread_mutex_lock(&mutA[i]);       // Also lock mutex immediately   
        sem_init(&sp[i], 0, 0);
        //finished[i] = FALSE;                
    }
   

    
    teacher();



    return 0;
}




