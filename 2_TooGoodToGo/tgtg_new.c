#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include "LinkedList.h"
// #include "toogood.h"

// TODO (Lukas) Move BREADS_RecentlySold and TICKS to CLI
#define BREADS_RecentlySold 20
#define TICKS 5 // Number of ticks before tgtg check

#define NO 0
#define YES 1

int strategy;
#define FIFO 0
#define SecondChance 1
#define NRU 2

char **BreadTypeNames;
int *RecentlySold;
int *OldBread;
int *TgtgBasket;
int NBBreadTypes;
LinkedList **Breads;
int BreadsToSell;
int BreadsSold;
int ticks;
int *BreadAmounts;
int tgtg_flag;
pthread_t tgtg_coordinator;
pthread_mutex_t mutTGTGFlag;



void bakeBreads(LinkedList* BreadType, int amount, int timestamp){
    for(int i = 0; i < amount; i++){
        addNode(BreadType,timestamp);
    }
}


void fifo(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        LinkedList* BreadType = Breads[i];
        int donate_counter = 0;
        while(BreadType->oldestBread >= timestamp - 2){ // Donate bread that is older than two ticks
            donate_counter += 1;
            removeNode(BreadType);
        }
        printf("We donated %d %s\n", donate_counter, BreadTypeNames[i]);
    }
}


void secondchance(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        LinkedList* BreadType = Breads[i];
        if(BreadType->tgtgBasket == NO){
            if(BreadType->oldestBread <= i-2){
                if(BreadType->recentlySold == NO){
                    BreadType->tgtgBasket = YES;
                    printf("%s was flagged for TGTG\n", BreadTypeNames[i]);
                }
            }
        }
        BreadType->recentlySold = NO;
    }
}


void nru(int timestamp){

}


void *tgtg_coordinate(){
    while(BreadsSold < BreadsToSell){
        sleep(20);
        pthread_mutex_lock(&mutTGTGFlag);
        tgtg_flag = YES;
        pthread_mutex_unlock(&mutTGTGFlag);
    }
    pthread_exit(0);
}


void tgtg(int strategy, int timestamp){
    if(strategy == FIFO){
        fifo(INT_MAX - timestamp);
    } else if (strategy == SecondChance){
        secondchance(INT_MAX - timestamp);
    } else {
        nru(INT_MAX - timestamp);
    }

    // Bake some new breads
    for(int j = 0; j < NBBreadTypes; j++){
        LinkedList* BreadType = Breads[j];
        if(BreadType->tgtgBasket == NO){
            bakeBreads(BreadType, BreadAmounts[j],INT_MAX-timestamp);
        }
    }
}


void sellBread(int timestamp){
    int type = rand() % NBBreadTypes;
    LinkedList *BreadType = Breads[type];
    if (length(BreadType) > 0){
        int timestamp = removeNode(BreadType);
        if (BreadType->tgtgBasket == NO){
            BreadType->recentlySold = YES;
        }
        printf("A bread was sold! Type: %s\n", BreadTypeNames[type]);
    } else {
        printf("Unfortunately there is no more %s left. We will bake some more.\n", BreadTypeNames[type]);
        bakeBreads(BreadType, BreadAmounts[type], timestamp);
    }
}

void runTGTG(char** names, int nbTypes, int* amounts, int max, int t, int s) {

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
    BreadTypeNames = names;
    NBBreadTypes= nbTypes;
    BreadAmounts = amounts;
    Breads = malloc(sizeof(LinkedList*)*NBBreadTypes);
    RecentlySold = malloc(sizeof(int)*NBBreadTypes);
    TgtgBasket = malloc(sizeof(int)*NBBreadTypes);
    ticks = t;
    strategy = s;
    BreadsSold = 0;
    tgtg_flag = NO;
    BreadsToSell = max;

    pthread_mutex_init(&mutTGTGFlag, NULL);
    pthread_create(&tgtg_coordinator, NULL, tgtg_coordinate, NULL);

    // Bake breads
    for(int i = 0; i < NBBreadTypes; i++){
        int type = i;
        Breads[type] = newList();
        bakeBreads(Breads[type], amounts[i],INT_MAX);
    }

    // Sell bread
    while(BreadsSold < BreadsToSell){
        sleep(1);
        sellBread(BreadsSold);
        BreadsSold += 1;
        pthread_mutex_lock(&mutTGTGFlag);
        if(tgtg_flag == YES){
            printf("Time to take a TGTG decision\n");
            tgtg_flag = NO;
            tgtg(strategy,BreadsSold);
        }
        pthread_mutex_unlock(&mutTGTGFlag);
    }
    return;
}


int main(int argc, char const *argv[]){
    char* BreadTypeNames[] = {"Croissant", "Zopf", "Tessinerli"};
    int num[3] = {3,3,3}; 
    runTGTG(BreadTypeNames,3,num, 20, 10, FIFO);
    return 0;
}

