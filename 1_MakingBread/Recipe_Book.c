
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Recipe_Book.h"


#define LEFT 0
#define RIGHT 1

#define FALSE 0
#define TRUE 1


/**
 *  @brief An InvRootNode (Inventory Root Node) is
 *  the root node of the data structure (binary tree)
 *  and stores the count of different bread types. 
 */
struct RecipeRootNode {
    struct BreadType* firstBreadType;   // Pointer to the first BreadType.
    int nbRecElem;                  // Number of different bread types.
};
typedef struct RecipeRootNode RecipeRootNode;


RecipeRootNode* pHead = NULL; // The Head of the data struct


/**
 * @brief Create a new BreadType with passed parameter.
 * 
 * @param name const char*
 * @return BreadType*
 */
BreadType* createBreadType(const char* name, int nbIngred, char** ingredArr)
{
    BreadType* pNode = malloc(sizeof(BreadType));   // allocate space in heap
    assert(pNode != NULL);             // just fail if we cannot get the required memory
    int len = (int) strlen(name);         // get length of 'name'
    pNode->breadName = malloc((len + 1) * sizeof(char));   // allocate enough space for the 'name' on the heap and store the pointer
    strcpy(pNode->breadName, name);   // copy the 'name' to the space in the heap
    pNode->nbIngred = nbIngred; // initialize nbIngred
    pNode->pLeft = NULL;        // initialize left leave
    pNode->pRight = NULL;       // initialize right leave
    pNode->pIngredArr = malloc((nbIngred+1) * sizeof(char*));   // initialize array for ingredient names
    pNode->pIngredArr[nbIngred] = NULL;    // declaring last entry as NULL
    for (int i = 0; i < nbIngred; ++i) {    // for each index initialize with ingredient from function variable ingredArr
        int len = (int) strlen(ingredArr[i]);   // get length of 'char*' in ingredArr[i]
        pNode->pIngredArr[i] = malloc((len + 1) * sizeof(char*));   // allocate enough space
        strcpy(pNode->pIngredArr[i], ingredArr[i]);     // copy 'char*' from ingredArr to pIngredArr
    }
    return pNode;
}


/**
 *  @brief Initializes the RecipeRootNode.
 */
void createRecipeRootNode()
{
    if (pHead == NULL) {    // check if no RecipeRootNode already exists
        pHead = malloc(sizeof(RecipeRootNode));    // allocate space in heap
        pHead->firstBreadType = NULL; // initialize pointer to first BreadType
        pHead->nbRecElem = 0;    // initialize nbRecElem
    }
}


/**
 * @brief Get the BreadType identified by 'name'. \n
 * Returns NULL if no such bread type is known.
 *
 * @param name
 */
BreadType* getBreadType(const char* name)
{
    BreadType* pCurrNode = pHead->firstBreadType;   // set pCurrNode to the first node in data structure
    while(pCurrNode != NULL) {                  // do until pCurrNode == NULL
        if (strcmp(name, pCurrNode->breadName) < 0) {  // if 'name' is smaller than the current 'ingredName'
            pCurrNode = pCurrNode->pLeft;               // set pCurrNode to left
        } else if (strcmp(name, pCurrNode->breadName) > 0) {   // if 'name' is bigger than the current 'ingredName'
            pCurrNode = pCurrNode->pRight;  // set pCurrNode to right
        } else {                //  if 'name' is equal to the current 'ingredName', i.e., found
            return pCurrNode;   // return the respective node
        }
    }
    return NULL;    // if no node or node not found
}


/** 
 * @brief Returns the ingredients array of a bread type specified by 'breadName'.
 *
 * @param breadName
 */
char** getIngredArray(const char* breadName)
{
    return getBreadType(breadName)->pIngredArr;     // gets the ingredients array of bread type specified by 'breadName'
}


/**
 * @brief Checks if the bread type specified already exists in
 * the data structure. Returns '1' it exists, '0' otherwise. \n
 *
 * @param name
 */
int containsBreadType(const char* name)
{
    if (getBreadType(name) != NULL) { // check if return is != NULL
        return TRUE;    // if != NULL, return '1'
    } else {
        return FALSE;   // if == NULL, return '0'
    }
}


/**
 * @brief Creates and inserts a new BreadType specified by 'name'
 * into the data structure, if not already present. \n
 * The nbIngred value denotes the number of different
 * ingredients necessary for this bread type. \n
 * The ingredArr contains all the ingredients' 'names'.
 *
 * @param name
 * @param nbIngred 
 * @param ingredArr
 */
void insertBreadType(const char* name, int nbIngred, char** ingredArr)
{

    BreadType *pNewNode = createBreadType(name, nbIngred, ingredArr);  // create specified BreadType
    BreadType *pCurrNode = pHead->firstBreadType; // assign first node of data structure to pCurrNode
    BreadType *pPrevNode = NULL;                // declare pPrevNode

    // No element in the data structure
    if (pCurrNode == NULL) {            // Check for no element
        pHead->firstBreadType = pNewNode; // make the newly created node the first node of the data structure
        pHead->nbRecElem += 1;          // increment the counter for the different bread types
        return;

    // > 0 elements in the data structure
    } else {
        int state;  // state variable to keep track of the sides 'LEFT' and 'RIGHT'
        while (pCurrNode) { // until the place for the new node to be inserted is found
            if (strcmp(pNewNode->breadName, pCurrNode->breadName) < 0) {  // if the pNewNode is lexically smaller compared to the pCurrNode
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
            pHead->nbRecElem += 1;          // increment the bread type counter
        } else { // if the last move was into the right subtree
            pPrevNode->pRight = pNewNode;   // insert pNewNode at the right leave of the pPrevNode
            pHead->nbRecElem += 1;          // increment the bread type counter
        }
    }
}


/**
 * @brief Register a new bread type in the recipe book.
 * Upper and lower case letters are differentiated. \n
 * The nbIngred value denotes the number of different
 * ingredients necessary for this bread type. \n
 * The ingredArr contains all the ingredients' 'names'.
 *
 * @param name
 * @param nbIngred
 * @param ingredArr
 */
int registerBreadType(const char* name , int nbIngred, char** ingredArr)
{
    if (pHead == NULL) {           // check if there is no pHead
        createRecipeRootNode();    // create pHead
    }

    if (!containsBreadType(name)) {            // if the bread type has not yet been registered
        insertBreadType(name, nbIngred, ingredArr);    // create and insert a new BreadType with identifying attribute 'name'
        return TRUE;
    } else {
        return FALSE;
    }
}


/**
 * @brief Prints the tree in 'inorder traversal'. Prints the node's name and stock count.
 *
 * @param pNode
 */
void printTreeRecursion(BreadType* pNode)
{
    if  (pNode == NULL) return;             // return if pNode is NULL
    printTreeRecursion(pNode->pLeft);       // traverse left subtree of pNode
    printf("Node name & ingredients: '%s' -> ", pNode->breadName);  // prints pNode
    for (int i = 0; i < pNode->nbIngred; i++) {         // for every index in ingredient array
        printf("%s; ", pNode->pIngredArr[i]);
    }
    printf("\n");
    printTreeRecursion(pNode->pRight);      // traverse right subtree of pNode
}


/**
 * @brief Lets the tree be printed in 'inorder traversal'. 
 * Values printed are the node's name and stock count.
 */
void printTree()
{
    printTreeRecursion(pHead->firstBreadType);    // calls the recursive print function
}


