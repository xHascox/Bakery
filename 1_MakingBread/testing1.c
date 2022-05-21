#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#include "exclusive_access_inventory.h"
#include "toogood.h"
*/
#include "1_MakingBread/exclusive_access_inventory.h"



int main(/*int argc, char const *argv[]*/) {

    //call

    int nbAppr = 5000;
    int maxBreads; = 1000; 
    int* nbIngrArr; 
    char*** ingrNames;
    int stonks = 20; 
    int nbBreadTypes = 1;
    char** breadTypesArr;
    int metric; 
    int scen;

    int maxStrLen = 32;

    nbIngrArr = malloc(nbBreadTypes*sizeof(int));
    nbIngrArr[0] = 1;

    ingrNames = malloc(nbBreadTypes*sizeof(char*));
    ingrNames[0] = malloc((nbIngrArr[0])*sizeof(char*)); 
    ingrNames[0][0] = malloc(maxStrLen*sizeof(char));
    strcpy(ingrNames[0][0], "IngredientY");

    breadTypesArr = malloc(nbBreadTypes*sizeof(char*));
    breadTypesArr[0] = malloc(maxStrLen*sizeof(char));
    strcpy(ingrNames[0][0], "BreadX");

    runMakingBread(nbAppr, maxBreads, nbIngrArr, ingrNames, stonks, nbBreadTypes, breadTypesArr, metric, scen);

}