#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#include "exclusive_access_inventory.h"
*/
#include "tgtg.h"


void checkOption(int* option);
void optionSelection();
void makingBread();
void tooGood();
void sleepingBaker();
void testingScripts();



int main(/*int argc, char const *argv[]*/) {

    if (argc > 1) { //automated testing when an argument is given
        //SYNTAX: ./main.o X [Y] [Z]
        // X = 1 // Making Bread
        if (atoi(argv[1]) == 1) {
        	int option = 3;
            int fast = 1;
        	if (argc > 2) {
        		option = atoi(argv[2]);
        	}
            if (argc > 3) {
        		fast = atoi(argv[3]);
        	}
        	autoMakingBread(option, fast);
        }

        // Y = 0 // Fairlearners
        // Y = 1 // Fastlearners
        // Y = 2 // Arrivalorder
        // Y = 3 // default, Prelearners (called fast learners in the project description)
        // Y = 4 // Scenario 2

        // Z = 0 // Slow test, the apprentices take some time to make bread, so the prints are printed slowly
        // Z = 1 // Fast test, so the apprentices bake bread as fast as they can, so the end statistics can be seen without waiting forever

        // X = 2 // Too Good To Go
        if (atoi(argv[1]) == 2) {
        	int algo = 1
            if (argc > 2) {
        		algo = atoi(argv[2]);
        	}
            autoTooGood(algo);
        }
        // Y = 0 // FIFO
        // Y = 1 // Second Chance
        // Y = 2 // NRU

        // X = 3 // Additional Feature Sleeping Baker
        
        if (atoi(argv[1]) == 3) {
        
        }

        
    }
    else {

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

void autoTooGood(int algo) {
    char* BreadTypeNames[] = {"Croissant", "Zopf", "Tessinerli", "BreadX", "BreadY", "BreadZ", "Bread1", "Flade", "SmallBread", "BigBread"};
    int num[10] = {30,30,30,30,30,30,30,30,30,30}; 
    runTGTG(BreadTypeNames,10,num, 290, 7, 10, algo);
}


/***************************************  MAKING BREAD  *********************************************/
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

    printf("Function call for Making Bread disabled for testing TGTG!\n");
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
        }
    }
    

    /* ENTERING AMOUNT OF BREADS SOLD */
    int breadsSold;
    printf("Next, please enter the amount of breads sold.\n");
    if (scanf("%d", &breadsSold) != 1) {       // Get user input for amount of sold Bread (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    
        exit(1);                                            
    }
    
    /* ENTERING AMOUNT OF ITERATIONS USED FOR APPLYING TOO GOOD TO GO "TICKS" */
    int ticks;
    printf("Next, please enter the amount of breads sold until the too good to go algorithm is applied, e.g. Ticks.\n");
    if (scanf("%d", &ticks) != 1) {       // Get user input for amount of Ticks (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    
        exit(1);                                            
    }

    /* ENTERING THE GRACE PERIOD */
    int grace;
    printf("Next, please enter the Grace Period.\n");
    if (scanf("%d", &grace) != 1) {       // Get user input for amount of Ticks (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    
        exit(1);                                            
    }

    /* ENTERING THE GRACE PERIOD */
    int algo;
    printf("Next, please enter the algorithm that should be applied (0=FIFO, 1=2ndChance, 2=NRU).\n");
    if (scanf("%d", &algo) != 1) {       // Get user input for amount of Ticks (int)
        printf("ERROR: Please enter a NUMBER (int)!\n");    
        exit(1);                                            
    }


    runTGTG(breadTypesArr, nbBreadTypes, nbBreads, breadsSold, ticks, grace, algo);

}
/******************************************  TGTG  **************************************************/

/*************************************  SLEEPING BAKER  *********************************************/
void sleepingBaker() {
    printf("Work in progress!\n");



}
/*************************************  SLEEPING BAKER  *********************************************/


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




