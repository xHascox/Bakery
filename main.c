#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


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
int flour = INT_MAX;
int oil = INT_MAX;
int bp = INT_MAX;   //baking powder
int breads = 0;     // # of breads made

/* FOR COMMUNICATION: APPRENTICE - TEACHER */
int finished[MAX_A];


/* NODE STRUCTURE */
struct Node {

    int apprNb; //apprentice
    
    struct Node *next;
    struct Node *prev; 

};


/* NEW NODE FUNCTION */
struct Node* newNode(int i) {

    // allocate Memory
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));

    // init data
    node->apprNb = i;
    node->next = NULL;
    node->prev = NULL; 

    return node;
}


struct Node *linkedList; // Kinda the Current node

/* CREATING NEW APPRENTICE AND ADDING TO LL */
void newApprentice(int apprentice) {

    if (!linkedList){
        linkedList = newNode(apprentice);
        
        return;
    }

    struct Node *newAppr = newNode(apprentice);

    newAppr->prev = linkedList;
    newAppr->next = linkedList->next;
    linkedList->next = newAppr;
    linkedList = newAppr;

    return;
}


void fireApprentice(int apprentice){


}

/* APPRENTICE FUNCTION */
void *apprentice(void *j){
    int i = (int) j;

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
        flour -= 1;
        oil -= 1;               
        bp -= 1;
            
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

    for (int i = 0; i < N ; i++){
        if(pthread_create(&threads[i], NULL, apprentice, (void *)i)){
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Thread %d created!\n", i);
            newApprentice(i);
        }
    }    


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