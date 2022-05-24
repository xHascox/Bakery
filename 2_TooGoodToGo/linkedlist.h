#ifndef LINKED_LIST
#define LINKED_LIST


struct TypeList dynTypes;

// Blueprint for different types of breads
struct BreadType {
    int id;         // Identifier
    char name[64];  // Name of bread type
    int nb;         // Number of breads of this type
};

/**
 * @brief 
 * The definition of the types
 */
struct TypeList {
  struct BreadType** types; // dynamic array
  int max;          // max number of dynamic types supported (todo: grow automatically)
  int count;        // current number of different types
  int* Sold;        // Types sold in the last k TICKS
  int* TgtgBasket;  // Types that are currently offered over TGTG
};

/**
 * @brief Initialize a new Type list. The supported number
 * of different types is fixed by parameter max.
 * @param max 
 */
void initTypeList(int max);

/**
 * @brief Add a new bread-type with passed name 
 * and the passed amount of this bread-type.
 * If the underlying type-list has reached maximum
 * of supported types, the addType request is ignored.
 * @param name 
 * @param nb 
 */
void addType(const char* name, int nb);

/**
 * @brief Just a helper to print all registered bread-types.
 */
void printTypes();



#endif