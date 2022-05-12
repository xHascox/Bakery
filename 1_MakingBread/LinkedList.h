#ifndef LINKED_LIST
#define LINKED_LIST

#include <stddef.h>
#include <stdbool.h>

struct Node {
    long id;
    struct Node* next;
};
typedef struct Node Node;

/**
 * @brief Every linked list is the amount of one ingredient.
 * 
 */
struct LinkedList {
    Node* pHead;
    char* name;    // The name of this linked-list. That must be an ingredient-name.
};
typedef struct LinkedList LinkedList;

/**
 * @brief Create a new Linked-List
 * 
 * @param initalSize  Number of Nodes initially set in the list
 * @param name The name (ingredient) this linked list stands for
 * @return LinkedList* 
 */
LinkedList* CreateLinkedList(size_t initalSize, const char* name);

/**
 * @brief Delete a linked list, releasing all resources held by that list
 * 
 * @param pList 
 */
void DeleteLinkedList(LinkedList* pList);

/**
 * @brief Get the numer of nodes in this Linked-List
 */
size_t getLength(LinkedList* pList);

/**
 * @brief Append one Node with a unique id to this Linked-List
 */
void appendNode(LinkedList* pList);

/**
 * @brief Removes the last element of the list. 
 * Returns true if an element was removed, false otherwise (list is empty)
 * 
 * @param pList 
 */
bool removeNode(LinkedList* pList);

#endif