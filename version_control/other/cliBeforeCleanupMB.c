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
        //tgtg();
    } else if (option == 3) {
        printf("You have chosen option three: %d\n", option);
        printf("\n\n");
        //sleepingBaker();
    } else if (option == 4) {
        printf("You have chosen option four: %d\n", option);
        printf("\n\n");
        //testingScripts();
    }
}

int main(/*int argc, char const *argv[]*/) {

    /* ----------------------------- */
    makingBread();
    /* ----------------------------- */

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

    /*
    int numberAp = 30;
    int maximalB = 100;
    int maxLen = 32;
    int* nbI;
    char*** IArr;
    int nbBT = 2;
    int nbIng01 = 2;
    int nbIng02 = 3;
    char** btName;
    int mentricc = 0;
    int scennar = 0;

	int toTheMoon = 200;

	nbI = malloc(nbBT*sizeof(int));
	nbI[0] = nbIng01;
	nbI[1] = nbIng02;

    btName = malloc(nbBT*sizeof(char*));
    btName[0] = malloc(maxLen*sizeof(char));
    btName[1] = malloc(maxLen*sizeof(char));

    strcpy(btName[0],"Bread01");
    strcpy(btName[1],"Bread02");


    IArr = malloc(nbBT*sizeof(char*));
    IArr[0] = malloc(nbIng01*sizeof(char*));
    IArr[0][0] = malloc(maxLen*sizeof(char));
    IArr[0][1] = malloc(maxLen*sizeof(char));
    IArr[1] = malloc(nbIng02*sizeof(char*));
    IArr[1][0] = malloc(maxLen*sizeof(char));
    IArr[1][1] = malloc(maxLen*sizeof(char));
    IArr[1][2] = malloc(maxLen*sizeof(char));

    strcpy(IArr[0][0],"flour");
    strcpy(IArr[0][1],"oil");
    strcpy(IArr[1][0],"oil");
    strcpy(IArr[1][1],"bp");
    strcpy(IArr[1][2],"flour");


    printf("Number of apprentices: %d\n", numberAp);
    printf("Number of breads to be made: %d\n", maximalB);
    printf("Number of bread types: %d\n", nbBT);
    printf("Stonks: %d\n", toTheMoon);
    printf("Metric: %d\n", mentricc);
    printf("Scenario: %d\n", scennar);
    
    printf("Number of ingredients array: ");
    for (int i = 0; i < nbBT; i++) {
        printf("%d -> ",nbI[i]);
    }
    printf("\n");
    printf("All the ingredient names: ");
    for (int i = 0; i < nbBT; i++){
        for (int j = 0; j < nbI[j]; j++){
            printf("%s -> ", IArr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("All the bread types: ");
    for (int i = 0; i < nbBT; i++){
        printf(" %s -> ", btName[i]);
    }
    printf("\n");


    runMakingBread(numberAp, maximalB, nbI, IArr, toTheMoon, nbBT, btName, mentricc, scennar);
    */



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
    printf("\n\n");
    breadTypesArr = malloc(nbBreadTypes*sizeof(char*));
    for (int i = 0; i < nbBreadTypes; i++) {
        breadTypesArr[i] = malloc(maxStrLen*sizeof(char));
    }


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
    //printf("BreadTypes Stored (first two) are: '%s' & '%s'\n", breadTypesArr[0], breadTypesArr[1]);
    nbIngrArr = malloc(nbBreadTypes*sizeof(int));
    
    printf("\n\n");

    /*  */
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
            // TODO ADD INGREDIENT TO INVENTORY (AND RECIPE)!!!
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
    metric = 0;
    scen = 0;

    printf("Number of apprentices: %d\n", nbAppr);
    printf("Number of breads to be made: %d\n", maxBreads);
    printf("Number of bread types: %d\n", nbBreadTypes);
    printf("Stonks: %d\n", stonks);
    printf("Metric: %d\n", metric);
    printf("Scenario: %d\n", scen);
    
    printf("Number of ingredients array: ");
    for (int i = 0; i < nbBreadTypes; i++) {
        printf("%d -> ",nbIngrArr[i]);
    }
    printf("\n");
    printf("All the ingredient names: ");
    for (int i = 0; i < nbBreadTypes; i++){
        for (int j = 0; j < nbIngrArr[j]; j++){
            printf("%s -> ", ingrNames[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("All the bread types: ");
    for (int i = 0; i < nbBreadTypes; i++){
        printf(" %s -> ", breadTypesArr[i]);
    }
    printf("\n");
    


    printf("Call to runMakingBread!\n");
    runMakingBread(nbAppr, maxBreads, nbIngrArr, ingrNames, stonks, nbBreadTypes, breadTypesArr, metric, scen);
    


}


void tgtg() {




}


void sleepingBaker() {




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




}


void testTgtg() {




}


void testAdditional() {




}


void testScenarios() {

    // adding the same item to the inventory

    // accessing the same item in the inventory

    // adding and removing same item at the same time

}




