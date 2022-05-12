#include "Inventory.h"

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

InventoryNode* pHead = NULL; // The first entry of the node

/**
 * @brief Returns the last of the list, the one where pNext is NULL
 * 
 * @return InventoryNode* 
 */
InventoryNode* GetLastNode()
{
    assert(pHead != NULL);
    InventoryNode* pLastNode = pHead;
    while(pLastNode->pNext != NULL)
    {
        pLastNode = pLastNode->pNext;
    }
    return pLastNode;
}


/**
 * @brief Create a new InventoryNode with passed paraemeters
 * 
 * @param name 
 * @param initialCount 
 * @return InventoryNode* 
 */
InventoryNode* CreateNode(const char* name, int initialCount)
{
    assert(strlen(name) > 0);
    assert(initialCount > 0);
    InventoryNode* pNode = malloc(sizeof(InventoryNode));
    assert(pNode != NULL);  // just fail if we cannot get the required memory
    // setup the newly created node:
    int len = strlen(name); 
    pNode->name = malloc((len + 1) * sizeof(char));
    assert(pNode->name != NULL);
    strcpy(pNode->name, name);
    pNode->count = initialCount;
    pNode->pNext = NULL;
    return pNode;
}

void RegisterIngredient(const char* name, int initialCount)
{
    InventoryNode* pNewNode = CreateNode(name, initialCount);
    // check if we are creating the very first element or if we need to append to the last node:
    if(pHead == NULL) {
        pHead = pNewNode;
    }
    else
    {
        InventoryNode* pLastNode = GetLastNode();
        pLastNode->pNext = pNewNode;
    }
}

InventoryNode* GetIngredientNode(const char* name)
{
    assert(strlen(name) > 0);
    InventoryNode* pNode = pHead;
    while(pNode != NULL)
    {
        if(strcmp(pNode->name, name) == 0)
        {
            return pNode;
        }
        pNode = pNode->pNext;
    }
    return NULL;
}

bool TakeIngredient(const char* name)
{
    InventoryNode* pNode = GetIngredientNode(name);
    if(pNode == NULL || pNode->count <= 0)
    {
        return false;
    }
    pNode->count--;
    return true;
}