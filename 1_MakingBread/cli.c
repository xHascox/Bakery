#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <ctype.h>
#include <string.h>

#include "inventory_BinTree.h"

void makingBread();
void tgtg();
void sleepingBaker();
void testingScripts();

int main(/*int argc, char const *argv[]*/) {

    /*
    please choose your program
    if 1: 
        makingBread()
    if 2:
        tgtg()
    if 3:
        sleepingBaker()
    if 4:
        Testing scripts()


    */
    
    


        return 0;
}


void makingBread() {

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
    
    //////////////////////////////////////////////////////////////
    /* TODO: ADD CLI FOR AMOUNT FOR EACH INGREDIENT TO BE ADDED */
    //////////////////////////////////////////////////////////////

    /* ENTERING RECIPE FOR BREADS (three ingredients) */
    printf("Now you are asked to enter three ingredients for each type of bread (max length %d). These ingredients may vary but do not have to.\n", maxStrLen);
    for (int i = 0; i < nbBreadTypes; i++){     // For every bread type
        for (int j = 0; j < 3; j++){            // there are three ingredients
            printf("For bread type '%s', please enter ingredient #%d : ", &breadTypes[i], j+1);
            scanf("%s", inputString);               // Get ingredient number j for bread i from user
            if (strlen(inputString) > maxStrLen){   // If the input for bread type name is greater than maxStrLen
                printf("ERROR: Your String is too long! It should not be greater than %d.\n", maxStrLen);   // print error
                exit(1);                                                                                    // and exit program
            }
            // ADD INGREDIENT TO INVENTORY (AND RECIPE)!!!

            printf("Ingredient #%d : %s \n\n", j+1, inputString);
        
        }
    }
    free(inputString);      // freeing aforementioned inputString
    printf("\n\n");
    

    /*
    for (int i = 0; i < nbBreadTypes; i++){
        printf("Bread type %d is: %s\n", i, &breadTypes[i]);
    }
    */



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




