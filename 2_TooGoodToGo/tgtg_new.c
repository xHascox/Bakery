#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <pthread.h>
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
int BreadsSold;
int ticks;
int *BreadAmounts;
int tgtg_flag;
pthread_t tgtg_coordinator;
pthread_mutex_t mutTGTGFlag;

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
    list->head->timestamp = 0;
    list->head->next = NULL;
    list->oldestBread = 0;
    list->recentlySold = NO;
    list->tgtgBasket = NO;
    return list;
}

void addNode(struct LinkedList* list, int t){
    struct Node* new = malloc(sizeof(struct Node));
    new->timestamp = t;
    new->next = NULL;
    struct Node* current = list->head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new;
    if(list->oldestBread <= t){
        list->oldestBread = t;
    }
}

int removeNode(struct LinkedList* list){
    struct Node* first = list->head->next;
    assert(first != NULL); // List empty
    struct Node* second = first->next;
    list->head->next = second;
    int t = first->timestamp;
    if(second != NULL){
        list->oldestBread = second->timestamp;
    } else {
        list->oldestBread = 0;
    }
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
        struct LinkedList* BreadType = Breads[j];
        if(BreadType->tgtgBasket == NO){
            bakeBreads(BreadType, BreadAmounts[j],INT_MAX-timestamp);
        }
    }
}

void fifo(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        struct LinkedList* BreadType = Breads[i];
        int donate_counter = 0;
        while(BreadType->oldestBread >= timestamp - 2){ // Donate bread that is older than two ticks
            donate_counter += 1;
            removeNode(BreadType);
        }
        printf("We donated %d %ss\n", donate_counter, BreadTypeNames[i]);
    }
}

void secondchance(int timestamp){
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

void nru(int timestamp){

}

void sellBread(int timestamp){
    int type = rand() % NBBreadTypes;
    struct LinkedList *BreadType = Breads[type];
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
    Breads = malloc(sizeof(struct LinkedList*)*NBBreadTypes);
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

