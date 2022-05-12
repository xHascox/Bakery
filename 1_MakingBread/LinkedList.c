#include "LinkedList.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

long counter = 0;   // we use a simple counter, incremented on every node created

Node* CreateNode()
{
    Node* pNode = (Node*) malloc(sizeof(Node));
    assert(pNode != NULL);
    pNode->id = counter++;
    pNode->next = NULL;
    return pNode;
}


LinkedList* CreateLinkedList(size_t initalSize, const char* name)
{
    LinkedList* pList = (LinkedList*) malloc(sizeof(LinkedList));
    assert(pList != NULL);
    pList->pHead = NULL;
    int len = strlen(name);     
    pList->name = malloc((len + 1) * sizeof(char));
    assert(pList->name != NULL);
    strcpy(pList->name, name);    
    while(initalSize > 0 )
    {
        appendNode(pList);
        initalSize--;
    }
    return pList;
}


void DeleteLinkedList(LinkedList* pList)
{
    assert(pList);
    while(getLength(pList) > 0)
    {
        removeNode(pList);
    }
    free(pList);
}


Node* getLastNode(LinkedList* pList) {
    assert(pList != NULL);
    assert(pList->pHead != NULL);
    Node* pLastNode = pList->pHead;
    while(pLastNode->next != NULL)
    {
        pLastNode = pLastNode->next;
    }
    return pLastNode;
}


void appendNode(LinkedList* pList)
{
    assert(pList != NULL);
    Node* pNewNode = CreateNode();
    if(pList->pHead == NULL)
    {
        pList->pHead = pNewNode;  // first node of the list
    }
    else
    {
        Node* pLastNode = getLastNode(pList);
        pLastNode->next = pNewNode;
    }
}


bool removeNode(LinkedList* pList)
{
    assert(pList != NULL);
    if(pList->pHead == NULL)
    {
        return false;
    }
    if(pList->pHead->next == NULL)
    {
        // The head is the only entry, delete it
        free(pList->pHead);
        pList->pHead = NULL;
    }
    else
    {
        // go through the list, searching for the second-last element
        Node* pNode = pList->pHead->next;
        Node* pPrev = pList->pHead;
        while(pNode->next != NULL)
        {
            pPrev = pNode;
            pNode = pNode->next;
        }
        free(pNode);
        pPrev->next = NULL;
    }
    return true;
}


size_t getLength(LinkedList* pList)
{
    Node* pNode = pList->pHead;
    size_t count = 0;
    while(pNode != NULL)
    {
        count++;
        pNode = pNode->next;
    }
    return count;
}