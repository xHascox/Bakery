
#include "Inventory.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    printf("just some testing with the inventory\n");
    // add some ingredients
    RegisterIngredient("first", 11);
    RegisterIngredient("second", 2);
    RegisterIngredient("third", 33);
    // now try to get them
    assert(GetIngredientNode("second")->count == 2);
    assert(GetIngredientNode("first")->count == 11);
    assert(GetIngredientNode("third")->count == 33);
    // get one that is not registered:
    assert(GetIngredientNode("fourth") == NULL);
    // add the missing one and get it:
    RegisterIngredient("fourth", 44);
    assert(GetIngredientNode("fourth")->count == 44);

    // take some ingredients out of stock until its empty
    assert(TakeIngredient("second") == true);
    assert(GetIngredientNode("second")->count == 1);
    assert(TakeIngredient("second") == true);
    assert(GetIngredientNode("second")->count == 0);
    // empty now, cannot take more. stock remains at 0
    assert(TakeIngredient("second") == false);
    assert(GetIngredientNode("second")->count == 0);
    printf("All tests passed fine\n");
}