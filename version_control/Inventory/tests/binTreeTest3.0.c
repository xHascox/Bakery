
#include <stdio.h>
#include "Inventory_BinTree.c"

int main(/*int argc, char *argv[]*/) {

    printf("Some Inventory Testing.\n");


    //int len = 3;

    /*
    char* testArr[] = {"hello", "test", "Nope", NULL};

    int i = 0;
    while (testArr[i]) {
        registerIngredient(testArr[i],10);
        setRestockTo(testArr[i],20);
        i++;
    }
    InvNode* firstInvNode = getFirstInvNode();

    printInvTree();
     */






    registerIngredient("Oil",5);
    setRestockTo("Oil",10);
    //printf("sdasd\n");
    registerIngredient("urDuck", 5);
    setRestockTo("urDuck",10);
    //printf("sdasd\n");
    registerIngredient("In", 5);
    setRestockTo("In",10);
    //printf("sdasd\n");
    registerIngredient("Beethoven's", 5);
    setRestockTo("Beethoven's",10);
    //printf("sdasd\n");
    registerIngredient("Anus", 5);
    setRestockTo("Anus",10);
    //printf("sdasd\n");
    registerIngredient("flour", 5);
    setRestockTo("flour",10);
    printf("Registered some ingredients:\n");
    printf("------------------------------\n\n");

    InvNode* firstInvNode = getFirstInvNode();

    printInvTree();
    printf("------------------------------\n\n");
    //*/



    restockIngredients();
    printf("Restocked all the ingredients!\n");
    printf("------------------------------\n\n");

    printInvTree();
    printf("------------------------------\n\n");



    takeIngredient("flour",3);
    if (takeIngredient("Oil",9)){
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



    printInvTree();
    printf("------------------------------\n\n");


    restockIngredients();
    printf("Restocked all the ingredients!\n");
    printf("------------------------------\n\n");

    printInvTree();
    printf("------------------------------\n\n");



    return 0;
}	