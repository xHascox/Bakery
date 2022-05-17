
#include <stdio.h>
#include "Inventory_BinTree.c"

int main(/*int argc, char *argv[]*/) {

    printf("Some Inventory Testing.\n");


    //int len = 3;

    char* testArr[] = {"hello", "test", "Nope", NULL};

    int i = 0;
    while (testArr[i]) {
        registerIngredient(testArr[i],10);
        i++;
    }

    InvRootNode * Head = getHead();


    /*
    registerIngredient("Oil", 10);
    //printf("sdasd\n");
    registerIngredient("urDuck", 10);
    //printf("sdasd\n");
    registerIngredient("In", 10);
    //printf("sdasd\n");
    registerIngredient("Beethoven's", 10);
    //printf("sdasd\n");
    registerIngredient("Anus", 10);
    //printf("sdasd\n");
    registerIngredient("flour", 10);
    printf("Registered some ingredients:\n");
    printf("------------------------------\n\n");

    //InvRootNode * Head = getHead();
    InvNode* invN01 = getInvNode("Oil");
    InvNode* invN02 = getInvNode("urDuck");
    InvNode* invN03 = getInvNode("In");
    InvNode* invN04 = getInvNode("Beethoven's");
    InvNode* invN05 = getInvNode("Anus");
    InvNode* invN06 = getInvNode("flour");


    printf("Ingred Name: %s \n", invN01->ingredName);
    printf("Ingred count: %d \n", invN01->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN02->ingredName);
    printf("Ingred count: %d \n", invN02->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN03->ingredName);
    printf("Ingred count: %d \n", invN03->count);
    printf("------------------------------\n\n");

    printf("Ingred Name: %s \n", invN04->ingredName);
    printf("Ingred count: %d \n", invN04->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN05->ingredName);
    printf("Ingred count: %d \n", invN05->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN06->ingredName);
    printf("Ingred count: %d \n", invN06->count);
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

    printf("Ingred Name: %s \n", invN01->ingredName);
    printf("Ingred count: %d \n", invN01->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN02->ingredName);
    printf("Ingred count: %d \n", invN02->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN03->ingredName);
    printf("Ingred count: %d \n", invN03->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN04->ingredName);
    printf("Ingred count: %d \n", invN04->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN05->ingredName);
    printf("Ingred count: %d \n", invN05->count);
    printf("------------------------------\n");

    printf("Ingred Name: %s \n", invN06->ingredName);
    printf("Ingred count: %d \n", invN06->count);
    printf("------------------------------\n\n");
    //*/

    return 0;
}	