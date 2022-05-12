//#include "IngredInv.h"

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <stdbool.h>

struct IngredNode {
    char* IngredName;
    struct IngredNode* pNextIngred;

};
typedef struct IngredNode IngredNode;

struct IngredInvNode {
    char* IngredName;         // The name of the item in
    int count;          // remaining stock of this item
    struct IngredInvNode* pNext;    // pointer to the next InvIngred node, NULL, if this is the last node
    struct IngredNode* pIngred;     // pointer to Linked List for specific ingredient

};
typedef struct IngredInvNode IngredInvNode;

struct InvHeadNode {
    struct IngredInvNode* firstInvNode;
    int nbInvElem;
};
typedef struct InvHeadNode InvHeadNode;


InvHeadNode* pHead = NULL; // The first entry of the InvList


/**
 * @brief Create a new IngredInvNode with passed paraemeters
 * 
 * @param name 
 * @param initialCount 
 * @return IngredInvNode* 
 */
IngredInvNode* CreateIngredInvNode(const char* name/*, int initialCount*/)
{
    assert(strlen(name) > 0);

    IngredInvNode* pNode = malloc(sizeof(IngredInvNode));
    assert(pNode != NULL);  // just fail if we cannot get the required memory
    // setup the newly created node:
    int len = strlen(name); 
    pNode->IngredName = malloc((len + 1) * sizeof(char));
    assert(pNode->IngredName != NULL);
    strcpy(pNode->IngredName, name);
    pNode->count = 0; //initialCount;
    pNode->pNext = NULL;
    pNode->pIngred = NULL;
    return pNode;
}

/** TODO CHANGE TO BIN SEARCH */
IngredInvNode* GetIngredInvNode(const char* name)
{
    assert(strlen(name) > 0);
    IngredInvNode* pNode = pHead->firstInvNode;
    while(pNode != NULL)
    {
        if(strcmp(pNode->IngredName, name) == 0)
        {
            return pNode;
        }
        pNode = pNode->pNext;
    }
    return NULL;
}

// TODO finish (changing) this method
IngredNode* CreateIngredNode(const char* name/*, int initialCount*/)
{
    assert(strlen(name) > 0);
    //assert(initialCount > 0);

    IngredNode* pNode = malloc(sizeof(IngredNode));
    assert(pNode != NULL);  // just fail if we cannot get the required memory
    IngredInvNode* IngredInvNode = GetIngredInvNode(name);

    pNode->IngredName = IngredInvNode->IngredName;
    assert(pNode->IngredName != NULL);
    pNode->pNextIngred = NULL;
    return pNode;
}

void CreateInvHeadNode()
{
    if (pHead == NULL) {
        pHead = malloc(sizeof(InvHeadNode));
        pHead->firstInvNode = NULL;
        pHead->firstInvNode = 0;
    }
}

bool containsIngred(const char* name) 
{
    if (GetIngredInvNode(name) != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// TODO: Maybe sort ingredients according to name
//       and finish GetLastIngredNode() or replace with equivalent


/**
 * @brief Returns the last of the list, the one where pNext is NULL
 * 
 * @return IngredInvNode* 
 */
IngredInvNode* GetLastInvNode()
{
    assert(pHead != NULL);
    IngredInvNode* pLastNode = pHead->firstInvNode;
    assert(pHead->nbInvElem > 0 );
    while(pLastNode->pNext != NULL)
    {
        pLastNode = pLastNode->pNext;
    }
    return pLastNode;
}


// TODO write doc
IngredNode* GetLastIngredNode(const char* name)
{
    IngredInvNode* ingredNode = GetIngredInvNode(name);
    assert(pHead->firstInvNode != NULL);
    if (ingredNode->pIngred != NULL)
    {
        IngredNode* pLastNode = ingredNode->pIngred;
        while(pLastNode->pNextIngred != NULL)
        {
            pLastNode = pLastNode->pNextIngred;
        }
        return pLastNode;
    }
    else
    {
        return NULL;
    }
    
}

// TODO: add adding a specified amount of ingredients  ---- DONE, I guess
void AddIngredient(const char* name, int amount) 
{
    IngredNode* pIngred = GetLastIngredNode(name);
    IngredInvNode* pIngrInv = GetIngredInvNode(name);
    if (pIngred == NULL)
    {
        pIngrInv->pIngred = CreateIngredNode(name);
        amount--;
        pIngrInv->count += 1;
        pIngred = pIngrInv->pIngred;
    }
    for (int i = 0; i < amount; i++)
    {
        pIngred->pNextIngred = CreateIngredNode(name);
        pIngrInv->count += 1;
        pIngred = pIngred->pNextIngred;
    }
}

// TODO: add amount taking
bool TakeIngredient(const char* name, int amount)
{
    IngredInvNode* pNode = GetIngredInvNode(name);
    if(pNode == NULL || pNode->count < amount || pNode->pIngred == NULL)
    {
        return false;
    }

    IngredNode* pIngredN; 
    for (int i = 0; i < amount; i++)
    {
        pIngredN = pNode->pIngred;
        pNode->pIngred = pIngredN->pNextIngred;
        free(pIngredN);
        pNode->count -= 1;
    }
    return true;
}

void InsertIngredientNode(const char* name)
{
    if (pHead == NULL)
    {
        CreateInvHeadNode();
    }
    if (!(containsIngred(name))) {

        IngredInvNode *pNewNode = CreateIngredInvNode(name /*, initialCount*/);
        IngredInvNode *pCurrNode = pHead->firstInvNode;
        IngredInvNode *pPrevNode = NULL;

        // check if we are creating the very first element or if we need to append to the last node:
        if (pHead->firstInvNode == NULL)   // Check for no element
        {
            pHead->firstInvNode = pNewNode;
            pHead->nbInvElem += 1;
            return;
        } else {   // any nb of elements
            do {
                if  (strcmp(pNewNode->IngredName, pCurrNode->IngredName) < 0)
                {
                    if (pHead->firstInvNode == pCurrNode)
                    {
                        pHead->firstInvNode = pNewNode;
                        pNewNode->pNext = pCurrNode;
                        pHead->nbInvElem += 1;
                        return;
                    } else {
                        pPrevNode->pNext = pNewNode;
                        pNewNode->pNext = pCurrNode;
                        pHead->nbInvElem += 1;
                        return;
                    }
                }

                pPrevNode = pCurrNode;
                pCurrNode = pCurrNode->pNext;
            } while (pCurrNode != NULL);

            pPrevNode->pNext = pNewNode;
            pHead->nbInvElem += 1;
            return;
        }
    }


}


void RegisterIngredient(const char* name , int initialCount)
{

    InsertIngredientNode(name);
    AddIngredient(name, initialCount);
}

IngredInvNode* getFirstInvNode()
{
    return pHead->firstInvNode;
}

InvHeadNode* getHead()
{
    return pHead;
}

