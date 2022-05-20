#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./1_MakingBread/exclusive_access_inventory.h"

void checkOption(int* option);
void optionSelection();
void makingBread();
void tgtg();
void sleepingBaker();
void testingScripts();


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


    printf("Hello World!\n");
    printf("You have started v0.8 of the Bakery!\n");
    printf("The following options are at your disposal:\n");
    printf(" -> Option 1: 'Making Bread'.\n");
    printf(" -> Option 2: 'To Good To Go'.\n");
    printf(" -> Option 3: 'Additional Feature'.\n");
    printf(" -> Option 4: 'Testing Scrips'.\n");
    printf("\n");


    printf("You are now asked to enter a number from one to four (1,2,3,4) to select an option.\n");
    optionSelection();
    

    return 0;
}


void makingBread() {

    int nbAppr;
    int maxBreads; 
    int* nbIngrArr; 
    char*** ingrNames;
    int stonks; 
    int nbBreadTypes;
    char** breadTypesArr;
    int metric; 
    int scen;

    int maxStrLen = 32;


    /* ENTERING AMOUNT OF BREAD TYPES */
    printf("Please enter the amount of bread types: ");
    if (scanf("%d", &nbBreadTypes) != 1) {       // Get user input for amount of bread (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    // If no int, print error
        exit(1);                                            // and exit program
    }
    breadTypesArr = malloc(nbBreadTypes*sizeof(char*));
    for (int i = 0; i < nbBreadTypes; i++) {
        breadTypesArr[i] = malloc(maxStrLen*sizeof(char));
    }

    printf("\n\n");


    /* ENTERING BREAD TYPES */
    char* inputString = malloc(maxStrLen*sizeof(char));      // malloc inputString for later removal
    printf("Great! Next, please enter a name for each bread type (max length %d).\n",maxStrLen);  
    for (int i = 0; i < nbBreadTypes; i++) {                 // For amount of bread types entered
        printf("Name for Bread type %d : ",i+1);            // 
        scanf("%s", inputString);                           // get bread name
        if (strlen(inputString) > maxStrLen) {               // If the input for bread type name is greater than maxStrLen
            printf("ERROR: Your String is too long! It should not be greater than %d.\n", maxStrLen);   
            exit(1);                                                                                    
        }
        strcpy(breadTypesArr[i], inputString);         // copy input to the data structure 
    }
    nbIngrArr = malloc(nbBreadTypes*sizeof(int));
    
    printf("\n\n");


<<<<<<< HEAD
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
=======
    /* ENTERING AMOUNT OF DIFFERENT INGREDIENTS NECESSARY FOR EACH BREAD TYPE */
    printf("Next, please enter the different amount of ingredients each bread type's recipe requires.\n");
    for (int i = 0; i < nbBreadTypes; i++) {
        printf("For bread type '%s': ", breadTypesArr[i]);
        if (scanf("%d", &nbIngrArr[i]) != 1) {       // Get user input for amount of ingredients (int)
            printf("ERROR: Please enter a NUMBER (int)!\n");    
            exit(1);                                            
        }
    }
    ingrNames = malloc(nbBreadTypes*sizeof(char*));
    for ( int i = 0; i < nbBreadTypes; i++) {
        ingrNames[i] = malloc((nbIngrArr[i])*sizeof(char*)); 
        for (int j = 0; j < nbIngrArr[i]; j++) {
            ingrNames[i][j] = malloc(maxStrLen*sizeof(char));
        }      
    }

    printf("\n\n");


    /* ENTERING RECIPE FOR BREADS */
    printf("Now you are asked to enter as many ingredients for each type of bread as before determined (max length of string: %d).\n", maxStrLen);
    for (int i = 0; i < nbBreadTypes; i++) {     // For every bread type
        for (int j = 0; j < nbIngrArr[i]; j++) {            // there are ingredients
            printf("For bread type '%s', please enter ingredient #%d : ", breadTypesArr[i], j+1);
>>>>>>> d9687d001c478840582f73fd99f9597ab27078e7
            scanf("%s", inputString);               // Get ingredient number j for bread i from user
            if (strlen(inputString) > maxStrLen) {   // If the input for bread type name is greater than maxStrLen
                printf("ERROR: Your String is too long! It should not be greater than %d.\n", maxStrLen);   
                exit(1);                                                                                    
            }
<<<<<<< HEAD
            // ADD INGREDIENT TO INVENTORY (AND RECIPE)!!!
            // add that ingredient, with an inital stock of 100
            addIngredient(inputString, 100);
            // and remember the ingredient name in the receipe
            r.ingredients[j] = malloc(strlen(inputString) * sizeof(char));
            strcpy(r.ingredients[j], inputString);

            printf("Ingredient #%d : %s \n\n", j+1, inputString);
=======
            strcpy(ingrNames[i][j], inputString);
            printf("Ingredient inserted #%d : %s \n", j+1, inputString);
>>>>>>> d9687d001c478840582f73fd99f9597ab27078e7
        }
        receipes[i] = r;    // and finally store that receipe
    }
    free(inputString);      // freeing inputString

    printf("\n\n");
<<<<<<< HEAD
    
    printInventory();
    printReceipes();
=======
>>>>>>> d9687d001c478840582f73fd99f9597ab27078e7


    printf("You also have to enter a desired amount of stock which is applied to each ingredient.\n");
    printf("Stock to be applied: ");
    if (scanf("%d", &stonks) != 1) {       
            printf("ERROR: Please enter a NUMBER (int)!\n");    
            exit(1);                                            
    }
    printf("\n\n");

    printf("Lastly, you have to provide some amounts for some variables.\n");
    printf("Please enter a desired amount for the number of apprentices: ");
    if (scanf("%d", &nbAppr) != 1) {       
            printf("ERROR: Please enter a NUMBER (int)!\n");   
            exit(1);                                            
    }

    printf("Please enter a desired amount for the number of breads to be made this day: ");
    if (scanf("%d", &maxBreads) != 1) {       
            printf("ERROR: Please enter a NUMBER (int)!\n");   
            exit(1);                                            
    }

    printf("\n\n");


    runMakingBread(nbAppr, maxBreads, nbIngrArr, ingrNames, stonks, nbBreadTypes, breadTypesArr, metric, scen);

}


void tgtg() {
    printf("Work in progress!\n");





}


void sleepingBaker() {
    printf("Work in progress!\n");



}


void checkOption(int* option) {
    
    printf("Please enter your option: ");
    if (scanf("%d", option) != 1) {
 
        printf("ERROR: Please enter a NUMBER (int)!\n");
        exit(1);
    }
    if (*option <= 0 || *option >= 5) {
        printf("Please choose from a number between one and four (1,2,3,4)!\n");
        checkOption(option);
    }
}


void optionSelection() {
    int option = 0;
    
    checkOption(&option);
 
    if (option == 1) {
        printf("You have chosen option one: %d\n", option);
        printf("\n\n");
        makingBread();
    } else if (option == 2) {
        printf("You have chosen option two: %d\n", option);
        printf("\n\n");
        tgtg();
    } else if (option == 3) {
        printf("You have chosen option three: %d\n", option);
        printf("\n\n");
        sleepingBaker();
    } else if (option == 4) {
        printf("You have chosen option four: %d\n", option);
        printf("\n\n");
        testingScripts();
    }
}



void testBaking();
void testTgtg();
void testAdditional();
void testScenarios();

void testingScripts() {
    printf("Work in progress!\n");

    /*
    please choose which part you would like to test
    if 1:
        testBaking()
    if 2:
        testTgtg()
    if 3:
        testAdditional()
    if 4:
        testScenarios()

    */


}


void testBaking() {
    printf("Work in progress!\n");



}


void testTgtg() {

    printf("Work in progress!\n");


}


void testAdditional() {
    printf("Work in progress!\n");



}


void testScenarios() {
    printf("Work in progress!\n");

    // adding the same item to the inventory

    // accessing the same item in the inventory

    // adding and removing same item at the same time

}




