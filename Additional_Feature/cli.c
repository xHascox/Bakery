#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#include "exclusive_access_inventory.h"
#include "toogood.h"
*/
#include "sleeping_baker.h"

void checkOption(int* option);
void optionSelection();
void makingBread();
void tooGood();
void sleepingBaker();
void testingScripts();
void autoMakingBread();



/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[]) {


    if (argc > 1) { //automated testing when an argument is given
        //SYNTAX: ./main.o X [Y] [Z]
        // X = 1 // Making Bread
        if (atoi(argv[1]) == 1) {
        	int option = 3;
        	if (argc > 2) {
        		option = atoi(argv[2]);
        	}
        	autoMakingBread(option); //TODO uncomment
        }

        // Y = 0 // Fairlearners
        // Y = 1 // Fastlearners
        // Y = 2 // Arrivalorder
        // Y = 3 // default, Prelearners (called fast learners in the project description)
        // Y = 4 // Scenario 2

        // X = 2 // Too Good To Go
        
        if (atoi(argv[1]) == 2) {
        	printf("tbd\n");
        }

        // X = 3 // Additional Feature Sleeping Baker
        
        // Y = Number of Customers
        // Z = Number of Chairs
        
        if (atoi(argv[1]) == 3) {
        	int nbCustomers = 30;
        	int nbChairs = 10;
        	if (argc > 2) {
        		nbCustomers = atoi(argv[2]);
        	}
        	if (argc > 3) {
        		nbChairs = atoi(argv[3]);
        	}
        	runAddF(nbCustomers, nbChairs);
        }

        
    }
    else { //manual testing
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
    }
    

    return 0;
}


/**********************************  COMMAND LINE OPTIONS  ******************************************/
/**
 * @brief Checks the user input for selecting an option.
 * 
 * @param option Pointer to int
 */ 
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

/**
 * @brief Handles the option selection for the command line interface (CLI). \n
 * There are four main options which can be selected by teh user: \n
 *  -> Learning to make bread; \n  
 *  -> Too Good To Go; \n
 *  -> Additional Feature - 'Sleeping Baker'; \n
 *  -> Testing Scripts;
 * 
 */
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
        tooGood();
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
/**********************************  COMMAND LINE OPTIONS  ******************************************/


/***************************************  MAKING BREAD  *********************************************/
/**
 * @brief Predefines the necessary arguments for the main run function for 'learning to make bread' and calls it. This funbction is mainly used for the testing scripts.
 * 
 * @param option 
 */
void autoMakingBread(int option) {
    int nbAppr = 3;
    int maxBreads = 10; 
    int* nbIngrArr; 
    char*** ingrNames;
    int stonks = 20; 
    int nbBreadTypes = 1;
    char** breadTypesArr;
    int metric = 3; 
    int scen = 0;

    int maxStrLen = 32;
    
    if (option == 4) {
    	scen = 2;
    }
    else {
    	metric = option;
    }

    nbIngrArr = malloc(nbBreadTypes*sizeof(int));
    nbIngrArr[0] = 1;

    ingrNames = malloc(nbBreadTypes*sizeof(char*));
    ingrNames[0] = malloc((nbIngrArr[0])*sizeof(char*)); 
    ingrNames[0][0] = malloc(maxStrLen*sizeof(char));
    strcpy(ingrNames[0][0], "IngredientY");

    breadTypesArr = malloc(nbBreadTypes*sizeof(char*));
    breadTypesArr[0] = malloc(maxStrLen*sizeof(char));
    strcpy(breadTypesArr[0], "BreadX");

    metric = 3; //prelearners = fast learners in documentation

    runMakingBread(nbAppr, maxBreads, nbBreadTypes, breadTypesArr, nbIngrArr, ingrNames, stonks, metric, scen);


}


/**
 * @brief This function is responsible for asking the user to enter the necessary arguments to run 'learning to make bread'. \n
 * 
 */
void makingBread() {

    int nbAppr;             // number of apprentices
    int maxBreads;          // Total amount of bread to be made
    int nbBreadTypes;       // number of different bread types
    char** breadTypesArr;   // array for each bread type's name
    int* nbIngrArr;         // array of int specifying the amount of ingredients each bread type needs; the index corresponds to the different bread types
    char*** ingrNames;      // array with size equal to the number of bread types, pointing to the amount of ingredients (strings) each bread type has.
    int stonks;             // amount of initial stock and 'restockTo'-value
    int metric;             // 
    int scen;

    int maxStrLen = 32;


    /* ENTERING AMOUNT OF BREAD TYPES */
    printf("Please enter the amount of bread types: ");
    if (scanf("%d", &nbBreadTypes) != 1) {       // Get user input for amount of bread (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    // If no int, print error
        exit(1);                                            // and exit program
    } else if (nbBreadTypes <= 0) {
        printf("Please only enter a positive number!\n");
        exit(1);
    } 
    breadTypesArr = malloc(nbBreadTypes*sizeof(char*));
    for (int i = 0; i < nbBreadTypes; i++) {
        breadTypesArr[i] = malloc(maxStrLen*sizeof(char));
    }
    nbIngrArr = malloc(nbBreadTypes*sizeof(int));

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
    
    printf("\n\n");


    /* ENTERING AMOUNT OF DIFFERENT INGREDIENTS NECESSARY FOR EACH BREAD TYPE */
    printf("Next, please enter the different amount of ingredients each bread type's recipe requires.\n");
    for (int i = 0; i < nbBreadTypes; i++) {
        printf("For bread type '%s': ", breadTypesArr[i]);
        if (scanf("%d", &nbIngrArr[i]) != 1) {       // Get user input for amount of ingredients (int)
            printf("ERROR: Please enter a NUMBER (int)!\n");    
            exit(1);                                            
        } else if (nbIngrArr[i] <= 0) {
        printf("Please only enter a positive number!\n");
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
            scanf("%s", inputString);               // Get ingredient number j for bread i from user
            if (strlen(inputString) > maxStrLen) {   // If the input for bread type name is greater than maxStrLen
                printf("ERROR: Your String is too long! It should not be greater than %d.\n", maxStrLen);   
                exit(1);                                                                                    
            }
            strcpy(ingrNames[i][j], inputString);
            printf("Ingredient inserted #%d : %s \n", j+1, inputString);
        }
    }
    free(inputString);      // freeing inputString

    printf("\n\n");

    /* STOCK TO BE APPLIED/restockTo VALUE */
    printf("You also have to enter a desired amount of stock which is applied to each ingredient.\n");
    printf("Stock to be applied: ");
    if (scanf("%d", &stonks) != 1) {       
            printf("ERROR: Please enter a NUMBER (int)!\n");    
            exit(1);                                            
    } else if (stonks <= 0) {
        printf("Please only enter a positive number!\n");
        exit(1);
    } 
    printf("\n\n");

    /* NUMBER OF APPRENTICES AND TOTAL NUMBER OF BREADS TO BE MADE */
    printf("Lastly, you have to provide some amounts for some variables.\n");
    printf("Please enter a desired amount for the number of apprentices: ");
    if (scanf("%d", &nbAppr) != 1) {       
            printf("ERROR: Please enter a NUMBER (int)!\n");   
            exit(1);                                            
    } else if (nbAppr <= 0) {
        printf("Please only enter a positive number!\n");
        exit(1);
    } 

    printf("Please enter a desired amount for the number of breads to be made this day: ");
    if (scanf("%d", &maxBreads) != 1) {       
            printf("ERROR: Please enter a NUMBER (int)!\n");   
            exit(1);                                            
    } else if (maxBreads <= 0) {
        printf("Please only enter a positive number!\n");
        exit(1);
    } 

    printf("\n\n");

    printf("Function call for Making Bread disabled for testing Sleeping Baker!\n");
    /* ----------------------------------------- */
    // runMakingBread(nbAppr, maxBreads, nbBreadTypes, breadTypesArr, nbIngrArr, ingrNames, stonks, metric, scen);
    /* ----------------------------------------- */
}
/***************************************  MAKING BREAD  *********************************************/


/******************************************  TGTG  **************************************************/
void tooGood() {

    char** breadTypesArr;
    int nbBreadTypes;
    int* nbBreads;

    int maxStrLen = 32;

    
    /* ENTERING AMOUNT OF BREAD TYPES */
    printf("Please enter the amount of bread types: ");
    if (scanf("%d", &nbBreadTypes) != 1) {       // Get user input for amount of bread (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    // If no int, print error
        exit(1);                                            // and exit program
    } else if (nbBreadTypes <= 0) {
        printf("Please only enter a positive number!\n");
        exit(1);
    } 
    breadTypesArr = malloc(nbBreadTypes*sizeof(char*));
    for (int i = 0; i < nbBreadTypes; i++) {
        breadTypesArr[i] = malloc(maxStrLen*sizeof(char));
    }
    nbBreads = malloc(nbBreadTypes*sizeof(int));
    
    printf("\n\n");


    /* ENTERING BREAD TYPES */
    char* inputString = malloc(maxStrLen*sizeof(char));     // malloc inputString for later removal
    printf("Great! Next, please enter a name for each bread type (max length %d).\n",maxStrLen);  
    for (int i = 0; i < nbBreadTypes; i++) {                // For amount of bread types entered
        printf("Name for Bread type %d : ",i+1);            // 
        scanf("%s", inputString);                           // get bread name
        if (strlen(inputString) > maxStrLen) {              // If the input for bread type name is greater than maxStrLen
            printf("ERROR: Your String is too long! It should not be greater than %d.\n", maxStrLen);   
            exit(1);                                                                                    
        }
        strcpy(breadTypesArr[i], inputString);              // copy input to the data structure 
    }
    free(inputString);
    
    printf("\n\n");


    /* ENTERING AMOUNT OF DIFFERENT INGREDIENTS NECESSARY FOR EACH BREAD TYPE */
    printf("Next, for each bread type, please enter the amount of breads in stock, i.e., to be sold.\n");
    for (int i = 0; i < nbBreadTypes; i++) {
        printf("For bread type '%s': ", breadTypesArr[i]);
        if (scanf("%d", &nbBreads[i]) != 1) {       // Get user input for amount of ingredients (int)
            printf("ERROR: Please enter a NUMBER (int)!\n");    
            exit(1);                                            
        } else if (nbBreads[i] <= 0) {
        printf("Please only enter a positive number!\n");
        exit(1);
        } 
    }
    
    printf("\n\n");


    printf("Function call for Making Bread disabled for testing Sleeping Baker!\n");
    /* ----------------------------------------- */
    // runTGTG(breadTypesArr, nbBreadTypes, nbBreads);
    /* ----------------------------------------- */
}
/******************************************  TGTG  **************************************************/

/*************************************  SLEEPING BAKER  *********************************************/
/**
 * @brief Handling the CLI for the additional feature and calls its run function. \n
 * Requested/Required arguments are the number of customers to be served and the amount of chairs for the customers to have a seat.
 * 
 */ 
void sleepingBaker() {

    int nbCustomers;
    int nbChairs;


    /* ENTERING AMOUNT OF CUSTOMERS */
    printf("Please enter the amount of customers: ");
    if (scanf("%d", &nbCustomers) != 1) {       // Get user input for amount customers (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    // If no int, print error
        exit(1);                                            // and exit program
    } else if (nbCustomers <= 0) {
        printf("Please only enter a positive number!\n");
        exit(1);
    }   


    /* ENTERING AMOUNT OF CHAIRS */
    printf("Please enter the amount of chairs: ");
    if (scanf("%d", &nbChairs) != 1) {       // Get user input for amount of chairs (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    // If no int, print error
        exit(1);                                            // and exit program
    } else if (nbChairs <= 0) {
        printf("Please only enter a positive number!\n");;
        exit(1);
    } 

    printf("\n\n");


    runAddF(nbCustomers, nbChairs);
}
/*************************************  SLEEPING BAKER  *********************************************/



void testBaking();
void testTgtg();
void testAdditional();
void testScenarios();

void testingScripts() {

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




