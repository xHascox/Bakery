#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0

Queue* init_queue() {
    Queue* new;
    new = malloc(sizeof(Queue));
    new->head = NULL;
    new->tail = NULL;
    new->nbElements = 0;

    return new;
}

void enqueue(Queue* q, sem_t* customer_semaphore) {
    Node* new = create_node(customer_semaphore);
    if (q->nbElements == 0) {
        new->previous = NULL;
        new->next = NULL;
        q->head = new;
        q->tail = new;
        q->nbElements++;
        
        return;
    }
    new->previous = q->tail;
    q->tail->next = new;
    new->next = NULL;
    q->tail = new;

    q->nbElements++;
    printf("EQ: %d\n", q->head->customer_semaphore);
}

/*
void move_to_tail(Queue* q, int customer_semaphore) {
    Node* tmp = q->head;
    while (tmp->customer_semaphore != customer_semaphore) {
        tmp = tmp->next;
    }

    if (tmp == q->tail) return;

    // now tmp is the node holding customer_semaphore
    if (tmp != q->head) {
        Node* prev = tmp->previous;
        prev->next = tmp->next;
        tmp->next->previous = prev;
    } else {
        q->head = q->head->next;
    }

    tmp->next = NULL;
    tmp->previous = q->tail;
    q->tail->next = tmp;
    q->tail = tmp;
}
*/ 
sem_t* dequeue(Queue* q) {
    // if (q->nbElements == 0) return void;
	printf("DQ: %d\n", q->head->customer_semaphore);
    Node* tmp = q->head;
    sem_t ret = q->head->customer_semaphore;

    if (q->nbElements > 1) {
        q->head = q->head->next;
        q->head->previous = NULL;
    } else {
        // meaning this is the last element to be dequeued
        q->head = NULL;
    }

    free(tmp);
    q->nbElements--;
    return &ret;
}

/*
Node* dequeue_node(Queue* q) {
    if (q->nbElements == 0) return NULL;

    Node* tmp = q->head;
    int ret = q->head->customer_semaphore;

    if (q->nbElements > 1) {
        q->head = q->head->next;
        q->head->previous = NULL;
    } else {
        // meaning this is the last element to be dequeued
        q->head = NULL;
    }

    free(tmp);
    q->nbElements--;


    return tmp;
}
*/

Node* create_node(sem_t* customer_semaphore) {
    Node* new = malloc(sizeof(Node));
    new->customer_semaphore = *customer_semaphore;
    return new;
}
/*
void print_queue(Queue* q) {
    Node* tmp = q->head;
    while (tmp != q->tail) {
        printf("{P %2d, R = %d} -> ", tmp->customer_semaphore, tmp->R);
        tmp = tmp->next;
    }
    printf("\n");
}
*/

//return length of Queue
int length(Queue* q) {
    return q->nbElements;
}

