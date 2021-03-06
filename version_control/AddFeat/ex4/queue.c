#include <stdio.h>
#include <stdlib.h>
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

void enqueue(Queue* q, int page) {
    int R = rand() % 2;
    Node* new = create_node(page, R);
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
}

void move_to_tail(Queue* q, int page) {
    Node* tmp = q->head;
    while (tmp->page != page) {
        tmp = tmp->next;
    }

    if (tmp == q->tail) return;

    // now tmp is the node holding page
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

int dequeue(Queue* q) {
    if (q->nbElements == 0) return -1;

    Node* tmp = q->head;
    int ret = q->head->page;

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

Node* dequeue_node(Queue* q) {
    if (q->nbElements == 0) return NULL;

    Node* tmp = q->head;
    int ret = q->head->page;

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

Node* create_node(int page, int R) {
    Node* new = malloc(sizeof(Node));
    new->page = page;
    new->R = R;
    return new;
}

void print_queue(Queue* q) {
    Node* tmp = q->head;
    while (tmp != q->tail) {
        printf("{P %2d, R = %d} -> ", tmp->page, tmp->R);
        tmp = tmp->next;
    }
    printf("\n");
}