#ifndef RECIPE_BOOK
#define RECIPE_BOOK


/**
 * @brief A BreadType (Recipe) Node stores the necessary ingredients in an array. \n
 * As we implement the Recipe as a binary tree, every BreadType can point to a left \n
 * (lexically smaller) or right (lexically bigger) node and to the array containing the ingredients.
 */
struct BreadType {                      // A bread type Node
    char* breadName;                    // The name of the bread type
    int nbIngred;                       // Number of ingredients needed for thi bread type
    struct BreadType* pLeft;            // Pointer to the left Recipe node
    struct BreadType* pRight;           // Pointer to the right Recipe node
    char** pIngredArr;                  // Pointer to Array for ingredient

};
typedef struct BreadType BreadType;


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
int registerBreadType(const char* name , int nbIngred, char** ingredArr);


/**
 * @brief Checks if the bread type specified already exists in
 * the data structure. Returns '1' it exists, '0' otherwise. 
 *
 * @param name
 */
int containsBreadType(const char* name);


/**
 * @brief Get the BreadType identified by 'name'. 
 * Returns NULL if no such bread type is known.
 *
 * @param name
 */
BreadType* getBreadType(const char* name);


/**
 * @brief Lets the tree be printed in 'inorder traversal'. 
 * Values printed are the node's name and stock count.
 */
void printTree();



#endif
