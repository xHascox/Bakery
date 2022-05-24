#ifndef RECIPE_BOOK
#define RECIPE_BOOK


/**
 * @brief A BreadType (Recipe) Node stores the necessary ingredients in an array. \n
 * As we implement the Recipe as a binary tree, every BreadType can point to a left \n
 * (lexicographically smaller) or right (lexicographically bigger) node and to the array containing the ingredients.
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
 * @param name Name of the bread type
 * @param nbIngred number of different ingredients necessary for this bread type
 * @param ingredArr array of ingredient's names (strings) 
 * @return int
 */
int registerBreadType(const char* name , int nbIngred, char** ingredArr);


/**
 * @brief Checks if the bread type specified already exists in
 * the data structure. Returns '1' it exists, '0' otherwise. 
 *
 * @param name Name of the bread type
 * @return int
 */
int containsBreadType(const char* name);


/**
 * @brief Get the BreadType identified by 'name'. 
 * Returns NULL if no such bread type is known.
 *
 * @param name Name of the bread type
 * @return BreadType*
 */
BreadType* getBreadType(const char* name);


/** 
 * @brief Returns the ingredients array of a bread type specified by 'breadName'.
 *
 * @param breadName Name of the bread type
 * @return char**
 */
char** getIngredArray(const char* breadName);


/**
 * @brief Get the the amount of different bread types.
 * 
 * @return int 
 */
int getNbBreadTypes();


/**
 * @brief Get number of different ingredients required for a with 'name' specified bread type.
 * 
 * @param name Name of the bread type
 * @return int 
 */
int getNbIngredOfBreadType(const char* name); 


/**
 * @brief Lets the tree be printed in 'inorder traversal'. 
 * Values printed are the node's name and stock count.
 */
void printRecipeBook();



#endif
