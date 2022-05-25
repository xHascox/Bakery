#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
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
struct LinkedList **Breads;
int BreadsToSell;
int ticks;
int maxBread;

struct LinkedList {
    struct Node* head;
    int oldestBread;
    int recentlySold;
    int tgtgBasket;
};

struct Node {
    int timestamp;
    struct Node *next;
};

struct LinkedList* newList(){
    struct LinkedList* list = malloc(sizeof(struct LinkedList));
    list->head = malloc(sizeof(struct Node));
    list->head->timestamp = INT_MAX;
    list->head->next = NULL;
    list->oldestBread = INT_MAX;
    list->recentlySold = NO;
    list->tgtgBasket = NO;
    return list;
}

void addNode(struct LinkedList* list, int t){
    struct Node* new = malloc(sizeof(struct Node));
    new->timestamp = t;
    struct Node* current = list->head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new;
}

int removeNode(struct LinkedList* list){
    struct Node* first = list->head->next;
    assert(first != NULL); // List empty
    struct Node* second = first->next;
    list->head->next = second;
    int t = first->timestamp;
    list->oldestBread = second->timestamp;
    list->recentlySold = YES;
    free(first);
    return t;
}

int length(struct LinkedList* list){
    int i = 0;
    struct Node* current = list->head;
    while(current->next != NULL){
        i += 1;
        current = current->next;
    }
    return i;
}

void bakeBreads(struct LinkedList* BreadType, int amount, int timestamp){
    for(int i = 0; i < amount; i++){
        addNode(BreadType,timestamp);
    }
}

void fifo(int i){
    for (int i = 0; i < NBBreadTypes; i++){
        struct LinkedList* BreadType = Breads[i];
        int donate_counter = 0; // TODO Continue here
        while(BreadType->oldestBread <= i-2 && BreadType->oldestBread != INT_MAX){ // Donate bread that is older than two ticks
            donate_counter += 1;
            removeNode(BreadType);
        }
        printf("We donated %d %ss\n", donate_counter, BreadTypeNames[i]);
    }
}

void secondchance(int i){
    for (int i = 0; i < NBBreadTypes; i++){
        struct LinkedList* BreadType = Breads[i];
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

void nru(int i){

}

void runTGTG(char** names, int nbTypes, int* amounts, int max, int t, int s) {

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
    BreadTypeNames = names;
    NBBreadTypes= nbTypes;
    // Breads = amounts;
    maxBread = max;
    Breads = malloc(sizeof(struct LinkedList*)*NBBreadTypes);
    RecentlySold = malloc(sizeof(int)*NBBreadTypes);
    TgtgBasket = malloc(sizeof(int)*NBBreadTypes);
    ticks = t;
    strategy = s;

    for(int i = 0; i < NBBreadTypes; i++){
        int type = i;
        Breads[type] = newList();
        bakeBreads(Breads[type], amounts[i],0);
    }

    
    /* Sell bread */
    srand(time(NULL));
    int type = 0;

    for (int i = 1; i <= maxBread; i++) {
        type = rand() % NBBreadTypes;
        struct LinkedList *BreadType = Breads[type];
        if (length(BreadType) > 0){
            int timestamp = removeNode(BreadType);
            if (BreadType->tgtgBasket == NO){
                BreadType->recentlySold = YES;
            }
            printf("A bread was sold! Type: %s, TGTG: %d\n", BreadTypeNames[type], Breads[type]->tgtgBasket);
            
            // Every k ticks, do a tgtg check
            if (i % ticks == 0){
                if(strategy == FIFO){
                    fifo(i);
                } else if (strategy == SecondChance){
                    secondchance(i);
                } else {
                    nru(i);
                }

                // Bake some new breads
                for(int j = 0; j < NBBreadTypes; j++){
                    struct LinkedList* BreadType = Breads[j];
                    if(BreadType->tgtgBasket == NO){
                        bakeBreads(BreadType, amounts[j],i);
                    }
                }
            }
        }
    }
}


int main(int argc, char const *argv[]){
    char* BreadTypeNames[] = {"Croissant", "Zopf", "Tessinerli"};
    int num[3] = {8,9,10}; 
    runTGTG(BreadTypeNames,3,num, 20, 4, FIFO);
}

