#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "LinkedList.h"


#define NO 0
#define YES 1



/**
 * @brief This is simply ????????????????????
 * 
 */
struct Node {
    int timestamp;
    struct Node *next;
};
typedef struct Node Node;


/**
 * @brief A new linked list struct is created and returned.
 * 
 * @return LinkedList* - Pointer to newly created LinkedList
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
 * @brief Created and adds a new Node with a timestamp 't' to the LinkedList. 
 * 
 * @param list Pointer to a LinkedList struct where a Node should be added to.
 * @param t The current timestamp
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
 * @brief Removes the first node of the LinkedList provided and returns its timestamp.
 * 
 * @param list Pointer to a LinkedList struct where the first Node should be removed from.
 * @return int - The timestamp stored in the removed node.
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
 * @brief Returns the lenght (amount of Nodes) of the provided LinkedList.
 * 
 * @param list Pointer to a LinkedList struct of which the length should be calculated.
 * @return int - Lenght of the LinkedList (amount of Nodes)
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

