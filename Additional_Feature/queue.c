#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0



/**
 * @brief Initializes a new queue and returns it.
 * 
 * @return Queue* 
 */
Queue* init_queue() {
    Queue* new;
    new = malloc(sizeof(Queue));
    new->head = NULL;
    new->tail = NULL;
    new->nbElements = 0;

    return new;
}


/**
 * @brief Create a new node with the customer's semaphore and returns it.
 * 
 * @param customer_semaphore The customer's specific semaphore with which one can wake the customer up.
 * @return Node* 
 */
Node* create_node(sem_t* customer_semaphore) {
    Node* new = malloc(sizeof(Node));
    new->customer_semaphore = customer_semaphore;
    return new;
}


/**
 * @brief Puts a with the passed arguments newly created node into the queue. \n
 * 
 * @param q Pointer to a queue to enqueue on.
 * @param customer_semaphore The customer's specific semaphore with which one can wake the customer up.
 */
void enqueue(Queue* q, sem_t* customer_semaphore) {
    Node* new = create_node(customer_semaphore);
    if (q->nbElements == 0) {
        new->previous = NULL;
        new->next = NULL;
        q->head = new;
        q->tail = new;
        q->nbElements++;
        
    } else {
    new->previous = q->tail;
    q->tail->next = new;
    new->next = NULL;
    q->tail = new;

    q->nbElements++;
    }
    return;
}


/**
 * @brief Get the first element's semaphore and delete/free the respective node afterwards. \n
 * 
 * @param q Pointer to a queue to dequeue on.
 * @return sem_t* 
 */
sem_t* dequeue(Queue* q) {
    // if (q->nbElements == 0) return void;
    Node* tmp = q->head;
    sem_t* ret = q->head->customer_semaphore;

    if (q->nbElements > 1) {
        q->head = q->head->next;
        q->head->previous = NULL;
    } else {
        // meaning this is the last element to be dequeued
        q->head = NULL;
    }

    free(tmp);
    q->nbElements--;
    return ret;
}


/**
 * @brief Return length of Queue
 * 
 * @param q Pointer to a queue to get the lenght of. 
 * @return int 
 */
int lengthQ(Queue* q) {
    return q->nbElements;
}

