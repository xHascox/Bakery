#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "LinkedList.h"


#define NO 0
#define YES 1



/**
 * @brief 
 * 
 */
struct Node {
    int timestamp;
    struct Node *next;
};
typedef struct Node Node;


/**
 * @brief 
 * 
 * @return LinkedList* 
 */
LinkedList* newList(){
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = malloc(sizeof(Node));
    list->head->timestamp = 0;
    list->head->next = NULL;
    list->oldestBread = INT_MAX;
    list->recentlySold = NO;
    list->totalSold = 0;
    list->totalDonated = 0;
    return list;
}


/**
 * @brief 
 * 
 * @param list 
 * @param t 
 */
void addNode(LinkedList* list, int t){
    Node* new = malloc(sizeof(Node));
    new->timestamp = t;
    new->next = NULL;
    Node* current = list->head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new;
    if(list->oldestBread >= t){
        list->oldestBread = t;
    }
}


/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int removeNode(LinkedList* list){
    Node* first = list->head->next;
    assert(first != NULL); // List empty
    Node* second = first->next;
    list->head->next = second;
    int t = first->timestamp;
    if(second != NULL){
        list->oldestBread = second->timestamp;
    } else {
        list->oldestBread = INT_MAX;
    }
    list->recentlySold = YES;
    free(first);
    return t;
}


/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int length(LinkedList* list){
    int i = 0;
    Node* current = list->head;
    while(current->next != NULL){
        i += 1;
        current = current->next;
    }
    return i;
}

