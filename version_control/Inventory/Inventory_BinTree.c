
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Inventory_BinTree.h"


#define LEFT 0
#define RIGHT 1

#define FALSE 0
#define TRUE 1


/**
 *  @brief An InvRootNode (Inventory Root Node) is
 *  the root node of the data structure (binary tree)
 *  and stores the number of different ingredients. \n
 *  There is only one root node for each data structure.
 */
struct InvRootNode {
    struct InvNode* firstInvNode;   // Pointer to the first InvNode.
    int nbInvElem;                  // Number of different ingredients.
};
typedef struct InvRootNode InvRootNode;

/*
struct AllInvNode {
    InvNode **EveryInvNodeArr;
    int count;
    //InvNode* firstNode;
    //InvNode* lastNode;
};
typedef struct AllInvNode AllInvNode;
 */

InvRootNode* pHead = NULL; // The Head of the InvList
//AllInvNode* AllInvNodes = NULL;

/**
 * @brief Create a new InvNode with passed parameter.
 * 
 * @param name const char*
 * @return InvNode*
 */
InvNode* createInvNode(const char* name)
{
    InvNode* pNode = malloc(sizeof(InvNode));   // allocate space in heap
    assert(pNode != NULL);             // just fail if we cannot get the required memory
    int len = (int) strlen(name);         // get length of 'name'
    pNode->ingredName = malloc((len + 1) * sizeof(char));   // allocate enough space for the 'name' on the heap and store the pointer
    strcpy(pNode->ingredName, name);   // copy the 'name' to the space in the heap
    pNode->count = 0;       // initialize count
    pNode->restockTo = 0;   // initialize restockTo
    pNode->pLeft = NULL;    // initialize left leave
    pNode->pRight = NULL;   // initialize right leave
    pNode->pIngred = NULL;  // initialize stock leave
    return pNode;
}


/**
 *  @brief Create and return a pointer to the IngredNode.
 *
 *  @param name
 *  @return IngredNode*
 */
IngredNode* createIngredNode()
{
    IngredNode* pNode = malloc(sizeof(IngredNode)); // allocate space in heap
    assert(pNode != NULL);          // just fail if we cannot get the required memory
    pNode->pNextIngred = NULL;      // initialize link to next node
    return pNode;
}


/**
 *  @brief Initializes the InvRootNode.
 *
 */
void createInvRootNode()
{
    if (pHead == NULL) {    // check if no InvRootNode already exists
        pHead = malloc(sizeof(InvRootNode));    // allocate space in heap
        pHead->firstInvNode = NULL; // initialize pointer to first InvNode
        pHead->nbInvElem = 0;    // initialize nbInvElem
    }
}


/**
 * @brief Get the InvNode identified by 'name'. \n
 * Returns NULL if no such ingredient is known.
 *
 * @param name
 * @return InvNode*
 */
InvNode* getInvNode(const char* name)
{
    InvNode* pCurrNode = pHead->firstInvNode;   // set pCurrNode to the first node in data structure
    while(pCurrNode != NULL) {                  // do until pCurrNode == NULL
        if (strcmp(name, pCurrNode->ingredName) < 0) {  // if 'name' is smaller than the current 'ingredName'
            pCurrNode = pCurrNode->pLeft;               // set pCurrNode to left
        } else if (strcmp(name, pCurrNode->ingredName) > 0) {   // if 'name' is bigger than the current 'ingredName'
            pCurrNode = pCurrNode->pRight;  // set pCurrNode to right
        } else {                //  if 'name' is equal to the current 'ingredName', i.e., found
            return pCurrNode;   // return the respective node
        }
    }
    return NULL;    // if no node or node not found
}


/**
 *  @brief Returns the last node of the specified
 *  ingredient stock. \n
 *  Returns NULL if \n
 *      - no respective InvNode exists; thus has to be registered first \n
 *      - an InvNode exists but no stock present
 *
 *  @param name
 *  @return IngredNode*
 */
IngredNode* getLastIngredNode(const char* name)
{
    InvNode* pInvNode = getInvNode(name);   // get the respective InvNode
    if (pInvNode == NULL) { // checks if InvNode exists
        return NULL;
    }
    if (pInvNode->pIngred != NULL) {    // checks if stock is present
        IngredNode* pLastNode = pInvNode->pIngred;  // declare an IngredNode -> first node in data structure
        while(pLastNode->pNextIngred != NULL) {     // until pLastNode == NULL
            pLastNode = pLastNode->pNextIngred;     // move forward
        }
        return pLastNode;   // return last node of stock
    } else {                // if no stock added
        return NULL;
    }
}


/**
 *  @brief Checks if the ingredient specified already exists in
 *  the data structure. Returns '1' it exists '0' otherwise. \n
 *  This function does not check the amount of a specific
 *  ingredient present.
 *
 *  @param name
 *  @return int
 */
int containsIngred(const char* name)
{
    if (getInvNode(name) != NULL) { // check if return is != NULL
        return TRUE;    // if != NULL, return '1'
    } else {
        return FALSE;   // if == NULL, return '0'
    }
}


/**
 *  @brief Add items to the data structure. The InvNode for
 *  the specified ingredient to be added to has to already
 *  exist in the data structure.
 *
 *  @param name
 *  @param amount
 */
void addIngredient(const char* name, int amount)
{
    InvNode* pInvNode = getInvNode(name); // declare an InvNode
    assert(pInvNode != NULL);             // check if != NULL
    IngredNode* pIngredNode = getLastIngredNode(name);  // declare an IngredNode
    if (pIngredNode == NULL) {  // if there is no stock of the specified ingredient
        pInvNode->pIngred = createIngredNode(name); // create an IngredNode and link it to the InvNode
        amount--;               // decrease function variable amount (important for the following for-loop)
        pInvNode->count += 1;   // increment stock counter
        pIngredNode = pInvNode->pIngred;    // move pIngredNode forward (important for the following for-loop)
    }
    for (int i = 0; i < amount; i++) {      // for the amount inserted
        pIngredNode->pNextIngred = createIngredNode(name);  // create new IngredNodes and insert into stock
        pInvNode->count += 1;                   // increment stock counter
        pIngredNode = pIngredNode->pNextIngred; // move pIngredNode forward
    }
}


/**
 * @brief Remove specified amount of items from the stock
 * of the passed ingredient. \n
 * Returns '0' if stock could not be reduced due to \n
 *      - not enough ingredients present \n
 *      - no such ingredient existing \n
 * and '1' otherwise.
 *
 * @param name
 * @return int
 */
int takeIngredient(const char* name, int amount)
{
    InvNode* pInvNode = getInvNode(name);   // get the specified InvNode
    if (pInvNode == NULL || pInvNode->count < amount || pInvNode->pIngred == NULL) { // do some checks
        return FALSE;           // return '0' if this ingredient has not been registered or there is not enough stock present
    }
    IngredNode* pIngredNode = NULL;    // declare an IngredNode
    for (int i = 0; i < amount; i++) {      // for the specified amount
        pIngredNode = pInvNode->pIngred;    // get the first element of the stock
        pInvNode->pIngred = pIngredNode->pNextIngred;   // make second element first element
        free(pIngredNode);  // free previous first element
        pInvNode->count -= 1;   // decrement stock counter
    }
    return TRUE;
}


/**
 *  @brief Creates and inserts a new InvNode specified by 'name'
 *  into the data structure, if not already present.
 *
 *  @param name
 */
void insertInvNode(const char* name)
{

    InvNode *pNewNode = createInvNode(name);  // create specified InvNode
    InvNode *pCurrNode = pHead->firstInvNode; // assign first node of data structure to pCurrNode
    InvNode *pPrevNode = NULL;                // declare pPrevNode

    // No element in the data structure
    if (pCurrNode == NULL) {            // Check for no element
        pHead->firstInvNode = pNewNode; // make the newly created node the first node fo the data structure
        pHead->nbInvElem += 1;          // increment the counter for the different ingredients
        return;

    // > 0 elements in the data structure
    } else {
        int state;  // state variable to keep track of the sides 'LEFT' and 'RIGHT'
        while (pCurrNode) { // until the place for the new node to be inserted is found
            if (strcmp(pNewNode->ingredName, pCurrNode->ingredName) < 0) {  // if the pNewNode is lexically smaller compared to the pCurrNode
                pPrevNode = pCurrNode;          // set pPrevNode
                pCurrNode = pCurrNode->pLeft;   // go into left subtree
                state = LEFT;                   // set state to 'LEFT'
            } else {    // if the pNewNode is lexically bigger compared to the pCurrNode
                pPrevNode = pCurrNode;          // set pPrevNode
                pCurrNode = pCurrNode->pRight;  // go into right subtree
                state = RIGHT;                  // set state to 'RIGHT'
            }
        }
        // Final insertion step
        if (state == LEFT) {    // if the last move was into the left subtree
            pPrevNode->pLeft = pNewNode;    // insert pNewNode at the left leave of the pPrevNode
            pHead->nbInvElem += 1;          // increment the stock counter
            return;
        } else { // if the last move was into the right subtree
            pPrevNode->pRight = pNewNode;   // insert pNewNode at the right leave of the pPrevNode
            pHead->nbInvElem += 1;          // increment the stock counter
            return;
        }
    }
}


/**
 * @brief Restocks the ingredients if a specified 'pNode' to its 'restockTo' value.
 *
 * @param pNode
 */
void restock(InvNode* pNode)
{
    int diff = pNode->restockTo - pNode->count;     // calculate the difference between the actual stock count and the restockTo amount
    if (diff != 0) {                                // when diff == 0, nothing to add
        addIngredient(pNode->ingredName, diff); // add the respective amount of ingredients
    }
}


/**
 * @brief Traverses the tree in 'inorder' and restocks every Node of it.
 *
 * @param pNode
 */
void restockRecursion(InvNode* pNode)
{
    if (pNode == NULL) return;              // return if pNode is NULL
    restockRecursion(pNode->pLeft);   // traverse left subtree of pNode
    restock(pNode);                         // restocks pNode
    restockRecursion(pNode->pRight);  // traverse right subtree of pNode
}


/**
 * @brief Restocks ingredients of every InvNode to the restockTo value.
 */
void restockIngredients()
{
    restockRecursion(pHead->firstInvNode);      // calls the traversal function.
}


/**
 * @brief Sets the 'restockTo' value of the pNode to the 'targetValue'.\n
 *
 * @param pNode
 * @param targetStock
 */
void setRestockToNode(InvNode* pNode, int targetStock)
{
    pNode->restockTo = targetStock;     // The 'restockTo' value is set to the 'targetStock' value..
}


/**
 * @brief Setter method for 'restockTo' (= 'targetStock') value of with 'name' specified InvNode.\n
 * IMPORTANT: the 'targetStock' value should be >= 5 to ensure a certain performance of the inventory.\n
 * A value > 10 is recommended. However, this value highly depends on the frequency in which this ingredient is used.
 *
 * @param name
 * @param targetStock
 */
void setRestockTo(const char* name, int targetStock)
{
    if (containsIngred(name)) {     // The ingredient defined by 'name' should already be in the data structure!
        setRestockToNode(getInvNode(name), targetStock);    // call to the actual setter method
    }
}


/**
 * @brief Register a new Ingredient in the inventory.
 * Upper and lower case letters are differentiated.\n
 * The initialAmount, if not set to '0', gets added to the
 * newly created InvNode.
 *
 * @param name
 * @param initialAmount
 */
void registerIngredient(const char* name , int initialAmount)
{
    if (pHead == NULL) {        // check if there is no pHead
        createInvRootNode();    // create pHead
    }

    if (!containsIngred(name)) {        // if the ingredient has not yet been registered
        insertInvNode(name);            // create and insert a new InvNode with identifying attribute 'name'
    }
    if (initialAmount) {            // if the initialAmount > 0
        addIngredient(name, initialAmount); // inserts initialAmount of IngredNodes
    }
}


/**
 * @brief Prints the tree in 'inorder traversal'. Prints the node's name and stock count.
 *
 * @param pNode
 */
void printTreeRecursion(InvNode* pNode)
{
    if  (pNode == NULL) return;                 // return if pNode is NULL
    printTreeRecursion(pNode->pLeft);     // traverse left subtree of pNode
    printf("Node name & count: '%s' -> %d\n", pNode->ingredName, pNode->count);  // prints pNode
    printTreeRecursion(pNode->pRight);    // traverse right subtree of pNode
}


/**
 * @brief Lets the tree be printed in 'inorder traversal'. Values printed are the node's name and stock count.
 */
void printTree()
{
    printTreeRecursion(pHead->firstInvNode);    // calls the recursive print function
}




///////////////////////////////////////
//  FOR DEBUG PURPOSES

InvRootNode* getHead() {
    return pHead;
}




/*
int indexAllInvNodes;

*/

/*
void getInOrderTraversal(InvNode* pNode) {
    if (pNode == NULL) return;
    getInOrderTraversal(pNode->pLeft);
    // ADD pNODE TO DATA STRUCT

}
 */

/*
InvNode** getAllInvNodes() {
    if (AllInvNode == NULL) {
        AllInvNode = malloc(sizeof(AllInvNodes*))
    }

    if ( == NULL)
    {
        AllInvNodes = malloc((pHead->nbInvElem)*sizeof(InvNode*));
    } else {
        free(AllInvNodes);
        AllInvNodes = malloc((pHead->nbInvElem)*sizeof(InvNode*));
    }



    return AllInvNodes;
}
 */

