#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//this file must probably be included by main.c
//but is this good program structure? who knows

#define BREAD_TYPES 2 //number of different bread types
#define BREADS_SOLD 5 //must be less than MAX_BREAD

// 
struct BreadType {
    int id;//name but as an int
    char name[64];//human readable identifier, e.g. "Tessinerli"
    int soldtime;//time when it has been sold most recently
    int k;//number of breads of this type
}


struct BreadType types[BREAD_TYPES];
//init BreadTypes
for (int i=0; i<BREAD_TYPES; i++) {
    types[i].id = i;
    //types[i].name = i; TODO
    types[i].soldtime = 0;
    types[i].k = 0;
}


//(1) create bread
//in the apprentice?, where bread+=1
    j = //breadtype to be created
    breads[j].k += 1;
    
        
//(2) sell bread
srand(time(NULL));
int nbrBreadsSold = BREADS_SOLD;//how many breads are being sold?
int type = 0;
for (int i=0; i<nbrBreadsSold; i++) {
    type = rand() % BREAD_TYPES;
    types[type].k -= 1;
    types[type].soldtime = i; //higher soldtime = later sold 
}
        
        
        
//(3)


