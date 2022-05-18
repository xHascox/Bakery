#ifndef RECIPE_BOOK
#define RECIPE_BOOK


/**
 * @brief A BreadType (Recipe) Node stores the three necessary ingredients in an array.\n
 * As we implement the Recipe as a binary tree with benefits, every BreadType can point to a left \n
 * (lexically smaller) or right (lexically bigger) node and to the array containing the ingredients.
 */
struct BreadType {                    // A bread type Node
    char* breadName;               // The name of the bread type
    int nbIngred;
    struct BreadType* pLeft;          // Pointer to the left Recipe node
    struct BreadType* pRight;         // Pointer to the right Recipe node
    char** pIngredArr;     // Pointer to Array for ingredient

};
typedef struct BreadType BreadType;


/**
 * @brief Register a new Ingredient in the Recipe.
 *
 * @param name
 * @param initialCount
 */
void registerIngredient(const char* name, int initialAmount);


/**
 *  @brief Checks if the ingredient specified already
 *  exists in the data structure. Returns '1' it exists
 *  '0' otherwise. This function does not check the amount
 *  of a specific ingredient present.
 *
 *  @param name
 *  @return int
 */
int containsBreadType(const char* name);


/**
 * @brief Get the BreadType identified by name.
 * Returns NULL if no such ingredient is known.
 *
 * @param name
 * @return BreadType*
 */
BreadType* getBreadType(const char* name);


/**
 * @brief Lets the tree be printed in 'inorder traversal'.
 */
void printTree();



#endif
