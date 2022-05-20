#ifndef INV_NINTREE
#define INV_BINTREE

#include <stdbool.h>


struct IngredNode {
    char* IngredName;
    //int count;
    struct IngredNode* pNextIngred;

};
typedef struct IngredNode IngredNode;


/**
 * @brief An InventoryNode stores on type of Ingredients.
 * Every ingredient has a count of the remaining stock,
 * and a name.
 * As we implement the inventory as a linked-list,
 * every InventoryNode can point to the next element in
 * the Linked-list
 */
struct IngredInvNode {
    char* IngredName;         // The name of the item in 
    int count;          // remaining stock of this item
    struct IngredInvNode* pNext;    // pointer to the next InvIngred node, NULL, if this is the last node
    struct IngredNode* pIngred;     // pointer to Linked List for specific ingredient
    
};
typedef struct IngredInvNode IngredInvNode;

/**
 * @brief Register a new Ingredient at the inventory
 * 
 * @param name 
 * @param initialCount 
 */
void RegisterIngredient(const char* name, int initialCount);

void AddIngredient(const char* name, int amount);

/**
 * @brief Get the Ingredient-node identified by name, returns NULL if no such ingredient is known
 * 
 * @param name 
 * @return InventoryNode* 
 */
IngredInvNode* GetIngredInvNode(const char* name);

/**
 * @brief Remove one item from the stock of the passed ingredient.
 * Returns true if stock was reduced by one, or false if stock is already empty
 * or no such ingredient is known by the inventory
 * 
 * @param name 
 * @return int 
 */
bool TakeIngredient(const char* name, int amount);

bool containsIngred(const char* name);






#endif