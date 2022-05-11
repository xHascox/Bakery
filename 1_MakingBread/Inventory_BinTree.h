#ifndef INV
#define INV

/**
 *  @brief An IngredNode (Ingredient Node) stores a pointer
 *  to the next IngredNode. \n
 *  This IngredNode does not have any other specific data. \n
 *  It is a representation for actual stock of this ingredient.
 */
struct IngredNode {
    struct IngredNode* pNextIngred;     // Pointer to the next Ingredient Node
};
typedef struct IngredNode IngredNode;


/**
 * @brief An InvNode (Inventory Node) stores one type of ingredient.
 * Every InvNode has a count of the remaining stock and a name.
 * As we implement the inventory as a binary tree with benefits,
 * every InvNode can point to a left (lexically smaller)
 * or right (lexically bigger) node and to the linked-list
 * containing the ingredients.
 */
struct InvNode {                    // An Inventory Node
    char* ingredName;               // The name of the item/ingredient
    int count;                      // Remaining stock of this item
    struct InvNode* pLeft;          // Pointer to the left Inventory node
    struct InvNode* pRight;         // Pointer to the right Inventory node
    struct IngredNode* pIngred;     // Pointer to Linked List for specific ingredient

};
typedef struct InvNode InvNode;


/**
 * @brief Register a new Ingredient in the inventory.
 *
 * @param name
 * @param initialCount
 */
void registerIngredient(const char* name, int initialAmount);


/**
 *  @brief Add items to the data structure. Respective
 *  ingredients are already registered.
 *
 *  @param name
 *  @param amount
 */
void addIngredient(const char* name, int amount);


/**
 * @brief Remove specified amount of items from the stock
 * of the passed ingredient.
 * Returns '0' if stock could not be reduced due to \n
 *      - not enough ingredients present \n
 *      - no such ingredient existing \n
 * and '1' otherwise.
 * @param name 
 * @return int 
 */
int takeIngredient(const char* name, int amount);


/**
 *  @brief Checks if the ingredient specified already
 *  exists in the data structure. Returns '1' it exists
 *  '0' otherwise. This function does not check the amount
 *  of a specific ingredient present.
 *
 *  @param name
 *  @return int
 */
int containsIngred(const char* name);


/**
 * @brief Get the InvNode identified by name.
 * Returns NULL if no such ingredient is known.
 *
 * @param name
 * @return InvNode*
 */
InvNode* getInvNode(const char* name);


#endif
