#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <ctype.h>
#include <string.h>

#include "LinkedList.h"

LinkedList** inventory; // an array we create dynamically to hold the inventory of ingredients
size_t inventoryLen;    // the size of the dynamically created array

/**
 * @brief Get the linked-list storing the ingredient with the passed name.
 * If no such ingredient is known, NULL is returned
 * 
 * @param name 
 * @return LinkedList* 
 */
LinkedList* getIngredient(const char* name)
{
    LinkedList* pList = NULL;
    for(int i = 0; i < inventoryLen; i++)
    {
        if(inventory[i] == NULL)
            break;  // we fill the array from front, if we encounter an empty place, we know no more data follows

        LinkedList* pTmp = inventory[i];
        if(strcmp(pTmp->name, name) == 0)
        {
            pList = pTmp;   // we found an entry in our inventory for this ingredient
            break;
        } 
    }
    return pList;
}

/**
 * @brief Add one ingredient to our inventory, with the passed initialStock.
 * Either a new entry is created in our inventory, or the stock of an existing
 * entry is incremented by the passed initialStock values (for example, if
 * two bread-types use the same ingredient, we want to have only one entry in the
 * inventory).
 * @param name 
 * @param initialStock 
 */
void addIngredient(const char* name, size_t initialStock)
{
    // search in our inventory, if we already have an entry for that ingredient
    LinkedList* pList = getIngredient(name);
    if(pList == NULL)
    {
        pList = CreateLinkedList(initialStock, name); // create a new entry in the inventory
        // and add that new entry at the very end of the list:
        for(int i = 0; i < inventoryLen; i++)
        {
            if(inventory[i] == NULL)
            {
                // we found an empty place, add it here
                inventory[i] = pList;
                break;
            }
        }
    }
    else
    {
        // just increment the stock of the already existing ingredient
        while(initialStock > 0)
        {
            appendNode(pList);
            initialStock--;
        }
    }
}

/**
 * @brief Just for fun, print the content of the inventory
 */
void printInventory()
{
    printf("Inventory:\n");
    for(int i = 0; i < inventoryLen; i++)
    {
        LinkedList* pList = inventory[i];
        if(pList != NULL)
        {
            size_t count = getLength(pList);
            printf("\tIngredient '%s' has %d items in stock\n", pList->name, count);
        }
    }
}

/**
 * @brief The struct defines a receipe for a bread-type
 */
struct Receipe
{
    char* name; // the name of the bread-type
    char* ingredients[3]; // the name of the 3 ingredients
};
typedef struct Receipe Receipe;
Receipe* receipes;
size_t receipesLen;

/**
 * @brief Just for fun, print the receipes known
 */
void printReceipes()
{
    printf("Receipes:\n");
    for(int i = 0; i < receipesLen; i++)
    {
        Receipe r = receipes[i];
        printf("\tReceipe '%s' needs those ingredients: '%s', '%s' and '%s'\n", r.name, r.ingredients[0], r.ingredients[1], r.ingredients[2]);
    }
}

int main(/*int argc, char const *argv[]*/) {

    int nbBreadTypes;
    int maxStrLen = 32;


    /* ENTERING AMOUNT OF BREAD TYPES */
    printf("Please enter the amount of bread types: ");
    if (scanf("%d", &nbBreadTypes) != 1){       // Get user input for amount of bread (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    // If no int, print error
        exit(1);                                            // and exit program
    }
    printf("\n\n");
    char breadTypes[nbBreadTypes][maxStrLen];   // array of strings containing the bread types


    /* ENTERING BREAD TYPES */
    char* inputString = (char*)malloc(sizeof(char)*maxStrLen);      // malloc inputString for later removal
    printf("Next, please enter a name for each bread type (max length %d).\n",maxStrLen);  
    for (int i = 0; i < nbBreadTypes; i++){                 // For amount of bread types entered
        printf("Name for Bread type %d : ",i+1);            // 
        scanf("%s", inputString);                           // get bread name
        if (strlen(inputString) > maxStrLen){               // If the input for bread type name is greater than maxStrLen
            printf("ERROR: Your String is too long! It should not be greater than %d.\n", maxStrLen);   // print error
            exit(1);                                                                                    // and exit program
        }
        
        // Maybe add LL for bread types, otherwhise an array is sufficient
        strcpy(breadTypes[i], inputString);         // copy input to the data structure 
    }
    printf("\n\n");
    
    //printf("Number of Bread Types: %d\n", nbBreadTypes);


    ////////////////////////////////
    /* init linked list inventory */
    ////////////////////////////////
    // The max number of ingredients can be nr-of-bread-types * 3:
    // Create an array to hold a linked-list for every ingredient.
    // Init every place in the inventory with a null-pointer (not used place)
    inventoryLen = nbBreadTypes * 3;
    inventory = (LinkedList**) malloc(sizeof(LinkedList*) * inventoryLen);
    memset(inventory, 0, sizeof(LinkedList*) * inventoryLen);

    // Also init the array to store the receipes
    receipesLen = nbBreadTypes;
    receipes = malloc(sizeof(Receipe) * receipesLen);

    //////////////////////////////////////////////////////////////
    /* TODO: ADD CLI FOR AMOUNT FOR EACH INGREDIENT TO BE ADDED */
    //////////////////////////////////////////////////////////////

    /* ENTERING RECIPE FOR BREADS (three ingredients) */
    printf("Now you are asked to enter three ingredients for each type of bread (max length %d). These ingredients may vary but do not have to.\n", maxStrLen);
    for (int i = 0; i < nbBreadTypes; i++){     // For every bread type
        // Create an entry for that receipe
        Receipe r;
        r.name = malloc(strlen(breadTypes[i]) * sizeof(char));
        strcpy(r.name, breadTypes[i]);
        for (int j = 0; j < 3; j++){            // there are three ingredients
            printf("For bread type '%s', please enter ingredient #%d : ", &breadTypes[i], j+1);
            scanf("%s", inputString);               // Get ingredient number j for bread i from user
            if (strlen(inputString) > maxStrLen){   // If the input for bread type name is greater than maxStrLen
                printf("ERROR: Your String is too long! It should not be greater than %d.\n", maxStrLen);   // print error
                exit(1);                                                                                    // and exit program
            }
            // ADD INGREDIENT TO INVENTORY (AND RECIPE)!!!
            // add that ingredient, with an inital stock of 100
            addIngredient(inputString, 100);
            // and remember the ingredient name in the receipe
            r.ingredients[j] = malloc(strlen(inputString) * sizeof(char));
            strcpy(r.ingredients[j], inputString);

            printf("Ingredient #%d : %s \n\n", j+1, inputString);
        }
        receipes[i] = r;    // and finally store that receipe
    }
    free(inputString);      // freeing aforementioned inputString
    printf("\n\n");
    
    printInventory();
    printReceipes();

    /*
    for (int i = 0; i < nbBreadTypes; i++){
        printf("Bread type %d is: %s\n", i, &breadTypes[i]);
    }
    */
 
    
    


        return 0;
}



