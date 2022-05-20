
#include <stdio.h>
#include "Recipe_Book.c"


int main(/*int argc, char *argv[]*/) {

    printf("Some Inventory Testing.\n");


    RecipeRootNode* Head = getHead();


    char* testBTArr[] = {"helloBread", "testBread", "Nope", "Berliner", "PaillasKP", "YESYESYES", "Ruchbrot", NULL};
    //printf("Adsasadassdsads\n");

    char* testIngredArr00[] = {"flour", "wheat", "water", "oil", "bp" }; // nb = 5
    //printf("Adsasadassdsads\n");
    char* testIngredArr01[] = {"wheat", "water", "bp", "oil", "flour" }; // nb = 5
    //printf("Adsasadassdsads\n");
    char* testIngredArr02[] = { "water", "bp", "oil"};  // nb = 3
    //printf("Adsasadassdsads\n");
    char* testIngredArr03[] = { "wheat", "water", "oil"};   // nb = 3
    //printf("Adsasadassdsads\n");
    char* testIngredArr04[] = { "oil", "bp"};   // nb = 2
    //printf("Adsasadassdsads\n");
    char* testIngredArr05[] = { "flour", "wheat", "water"}; // nb = 3
    //printf("Adsasadassdsads\n");
    char* testIngredArr06[] = { "flour", "oil", "water"};   // nb = 3
    //printf("Adsasadassdsads\n");

    int index[] = {5,5,3,3,2,3,3};
    //printf("Adsasadassdsads\n");
    char** A[] = {testIngredArr00, testIngredArr01, testIngredArr02, testIngredArr03, testIngredArr04, testIngredArr05, testIngredArr06};
    //printf("Adsasadassdsads\n");

    int i = 0;
    while (testBTArr[i]) {
        registerBreadType(testBTArr[i], index[i], A[i]);
        printf("Adsasadassdsads\n");
        //setRestockTo(testBTArr[i],10);
        i++;
    }

    printTree();
    printf("------------------------------\n\n");



    /*//*
    registerIngredient("Oil",0);
    setRestockTo("Oil",10);
    //printf("sdasd\n");
    registerIngredient("urDuck", 0);
    setRestockTo("urDuck",10);
    //printf("sdasd\n");
    registerIngredient("In", 0);
    setRestockTo("In",10);
    //printf("sdasd\n");
    registerIngredient("Beethoven's", 0);
    setRestockTo("Beethoven's",10);
    //printf("sdasd\n");
    registerIngredient("Anus", 0);
    setRestockTo("Anus",10);
    //printf("sdasd\n");
    registerIngredient("flour", 0);
    setRestockTo("flour",10);
    printf("Registered some ingredients:\n");
    printf("------------------------------\n\n");

    printTree(Head->firstBreadType);
    printf("------------------------------\n\n");



    restockIngredients();
    printf("Restocked all the ingredients!\n");
    printf("------------------------------\n\n");

    printTree(Head->firstBreadType);
    printf("------------------------------\n\n");



    takeIngredient("flour",3);
    if (takeIngredient("Oil",11)){
        printf("Oil successfully removed!\n");
    } else {
        printf("Could not remove Oil; NEED TO INVADE! GOD PRAISE MMMMMMMUUURRRRRRRICAAA!!!!\n");
    }
    if (takeIngredient("urDuck",10)){
        printf("urDuck successfully removed!\n");
    } else {
        printf("Could not remove urDuck, U dont have any duck :( \n");
    }
    takeIngredient("Anus", 2);
    takeIngredient("Beethoven's", 10);
    takeIngredient("In",1);

    printf("Some ingredients taken!\n");
    printf("------------------------------\n\n");
    //*/


    printTree();
    printf("------------------------------\n\n");

    return 0;
}	