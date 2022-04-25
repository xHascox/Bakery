#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//this file must probably be included by main.c
//but is this good program structure? who knows

#define BREAD_TYPES 2 //number of different bread types
#define BREADS_SOLD 5 //must be less than MAX_BREAD

// Blueprint for different types of breads
struct BreadType {
    int id;//name but as an int
    char name[64];//human readable identifier, e.g. "Tessinerli"
    int soldtime;//time when it has been sold most recently
    int k;//number of breads of this type
}

// The types of bread the bakery offers
struct BreadType types[BREAD_TYPES];

for (int i=0; i<BREAD_TYPES; i++) {
    types[i].id = i;
    //types[i].name = i; TODO
    types[i].soldtime = 0;
    types[i].k = 0;
}


//(1) Create bread
//in the apprentice?, where bread+=1
    j = //breadtype to be created
    breads[j].k += 1;
    
        
//(2) Sell bread
srand(time(NULL));
int nbrBreadsSold = BREADS_SOLD;//how many breads are being sold?
int type = 0;
for (int i=0; i<nbrBreadsSold; i++) {
    type = rand() % BREAD_TYPES;
    types[type].k -= 1;
    types[type].soldtime = i; //higher soldtime = later sold 
}
        
             
//(3)


