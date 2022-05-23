#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exclusive_access_inventory.h"

void checkOption(int* option);
void optionSelection();
void makingBread();
void tgtg();
void sleepingBaker();
void testingScripts();
void autoMakingBread();



int main(int argc, char const *argv[]) {
    if (argc > 1) { //automated testing when an argument is given
        //SYNTAX: ./main.o X [Y] 
        // X = 1 // Making Bread
        if (atoi(argv[1]) == 1) {
        	int option = 3;
        	if (argc > 2) {
        		option = atoi(argv[2]);
        	}
        	autoMakingBread(option);
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
        
        if (atoi(argv[1]) == 3) {
        
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

    runMakingBread(nbAppr, maxBreads, nbIngrArr, ingrNames, stonks, nbBreadTypes, breadTypesArr, metric, scen);


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




