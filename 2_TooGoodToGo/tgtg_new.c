#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "LinkedList.h"

// Readability
#define NO 0
#define YES 1

// Paging Algorithms
int strategy;
#define FIFO 0
#define SECOND_CHANCE 1
#define NRU 2


// Global Variables
char **BreadTypeNames;
int *RecentlySold;
int NBBreadTypes;
LinkedList **Breads;
int BreadsToSell;
int BreadsSold;
int ticks;
time_t currentTime;
int grace_period;
int *BreadAmounts;
int tgtg_flag;
pthread_t tgtg_coordinator;
pthread_mutex_t mutTGTGFlag;

// Functions
void bakeBreads(LinkedList* BreadType, char *name, int amount, int timestamp);
void *tgtg_coordinate();
void tgtg(int strategy, int timestamp);
void fifo(int timestamp);
void secondchance(int timestamp);
void nru(int timestamp);
void sellBread(int timestamp);
void runTGTG(char** names, int nbTypes, int* amounts, int max, int t, int p, int s);


/**
 * @brief Creates a specified amount of bread for a specified BreadType.
 * 
 * @param BreadType The LinkedList for a specific BreadType
 * @param name Name of the specific BreadType
 * @param amount Amount of specified BreadType produced
 * @param timestamp Timestamp of when created
 */
void bakeBreads(LinkedList* BreadType, char *name, int amount, int timestamp){
    for(int i = 0; i < amount; i++){
        addNode(BreadType,timestamp);
    }
    printf("Produced %d %ss at time %d\n", amount, name, timestamp);
}


/**
 * @brief This thread coordinates the entire process using a mutex with which it can lock the control flow.
 * It sleeps for the defined amount of ticks to make the process more readable.
 * 
 * @return void* 
 */
void *tgtg_coordinate(){
    while(BreadsSold < BreadsToSell){
        sleep(ticks);
        pthread_mutex_lock(&mutTGTGFlag);
        tgtg_flag = YES;
        pthread_mutex_unlock(&mutTGTGFlag);
    }// The oldest Bread
}


/**
 * @brief 
 * 
 * @param strategy 
 * @param timestamp 
 */
void tgtg(int strategy, int timestamp){
    if(strategy == FIFO){
        fifo(timestamp);
    } else if (strategy == SECOND_CHANCE){
        secondchance(timestamp);
    } else {
        nru(timestamp);
    }

    for(int i = 0; i < NBBreadTypes; i++){
        LinkedList* BreadType = Breads[i];
        BreadType->recentlySold = NO;
    }
}


/**
 * @brief 
 * 
 * @param timestamp 
 */
void fifo(int timestamp){
    printf("We donate all the breads produced before %d\n", timestamp - grace_period);
    for (int i = 0; i < NBBreadTypes; i++){
        LinkedList* BreadType = Breads[i];
        int donate_counter = 0;
        while(BreadType->oldestBread <= timestamp - grace_period){ // Donate bread that is older than two ticks
            donate_counter += 1;
            time_t t = removeNode(BreadType);
        }
        BreadType->totalDonated += donate_counter;
        printf("We donated %d %ss\n", donate_counter, BreadTypeNames[i]);
    }
}


/**
 * @brief 
 * 
 * @param timestamp 
 */
void secondchance(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        LinkedList* BreadType = Breads[i];
        if(BreadType->oldestBread <= timestamp - grace_period){
            if(BreadType->recentlySold == NO){
                int donate_counter = 0;
                while(BreadType->oldestBread <= timestamp - grace_period){ // Donate bread that is older than two ticks
                    donate_counter += 1;
                    removeNode(BreadType);
                }
                BreadType->totalDonated += donate_counter;
                printf("We donated %d %ss\n", donate_counter, BreadTypeNames[i]);
            } else {
                printf("We do not donate %s because it was recently sold.\n", BreadTypeNames[i]);
            }
        } else {
            printf("We do not donate %s because there are no old %ss.\n", BreadTypeNames[i], BreadTypeNames[i]);
        }
    }
}


/**
 * @brief 
 * 
 * @param timestamp 
 */
void nru(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        LinkedList* BreadType = Breads[i];
        if(BreadType->recentlySold == NO){
            int donate_counter = 0;
            while(length(BreadType) > 0){ // Donate bread that is older than two ticks
                donate_counter += 1;
                removeNode(BreadType);
            }
            BreadType->totalDonated += donate_counter;
            printf("We donated %d %ss\n", donate_counter, BreadTypeNames[i]);
        } else {
            printf("We do not donate %s because it was recently sold.\n", BreadTypeNames[i]);
        }
    }
}


/**
 * @brief 
 * 
 * @param timestamp 
 */
void sellBread(int timestamp){
    int type = rand() % NBBreadTypes;
    LinkedList *BreadType = Breads[type];
    if (length(BreadType) > 0){
        int timestamp = removeNode(BreadType);
        BreadType->recentlySold = YES;
        BreadType->totalSold += 1;
        printf("A bread was sold! Type: %s\n", BreadTypeNames[type]);
    } else {
        printf("Unfortunately there is no more %s left. We will bake some more.\n", BreadTypeNames[type]);
        bakeBreads(BreadType, BreadTypeNames[type], BreadAmounts[type], timestamp);
        time_t timestamp = removeNode(BreadType);
        BreadType->recentlySold = YES;
        BreadType->totalSold += 1;
        printf("A bread was sold! Type: %s\n", BreadTypeNames[type]);
    }
}


/**
 * @brief 
 * 
 * @param names Array of strings (char*) with names of bread types
 * @param nbTypes Number of bread types
 * @param amounts Array of int for each bread type specifying the amount of breads to be baked  and subsequently sold
 * @param max Amount of breads to sell
 * @param _ticks Amount of ticks to wait between each run of an algorithm
 * @param _grace_period Amount of ticks to wait until bread is donated
 * @param _strategy Strategy definign which algorithm to use
 */
void runTGTG(char** names, int nbTypes, int* amounts, int max, int _ticks, int _grace_period, int _strategy) {

    printf("--- start ---\n");

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
    BreadTypeNames = names;
    NBBreadTypes= nbTypes;
    BreadAmounts = amounts;
    Breads = malloc(sizeof(LinkedList*)*NBBreadTypes);
    RecentlySold = malloc(sizeof(int)*NBBreadTypes);
    ticks = _ticks;
    strategy = _strategy;
    BreadsSold = 0;
    tgtg_flag = NO;
    BreadsToSell = max;
    grace_period = _grace_period;
    currentTime = time(NULL);

    pthread_mutex_init(&mutTGTGFlag, NULL);
    pthread_create(&tgtg_coordinator, NULL, tgtg_coordinate, NULL);

    // Bake breads
    for(int i = 0; i < NBBreadTypes; i++){
        int type = i;
        Breads[type] = newList();
        currentTime = time(NULL);
        bakeBreads(Breads[type], BreadTypeNames[type], amounts[i], currentTime);
    }

    // Sell bread
    while(BreadsSold < BreadsToSell){
        sleep(1);
        currentTime = time(NULL);
        sellBread(currentTime);
        BreadsSold += 1;
        pthread_mutex_lock(&mutTGTGFlag);
        if(tgtg_flag == YES){
            printf("----------------------------\n");
            printf("Time to take a TGTG decision:\n");
            tgtg_flag = NO;
            currentTime = time(NULL);
            tgtg(strategy,currentTime);
            printf("----------------------------\n");
        }
        pthread_mutex_unlock(&mutTGTGFlag);
    }

    printf("----------------------------\n");
    printf("Summary:\n\n");
    for(int i = 0; i < NBBreadTypes; i++){
        int type = i;
        printf("%s:\n",BreadTypeNames[type]);
        printf("    Sold: %d\n", Breads[type]->totalSold);
        printf("    Donated: %d\n", Breads[type]->totalDonated);
    }

    printf("--- stop ---\n");

    return;
}


int main(int argc, char const *argv[]){
    char* BreadTypeNames[] = {"Croissant", "Zopf", "Tessinerli", "Bli", "Bla", "Blu"};
    int num[6] = {3,3,3,3,3,3}; 
    runTGTG(BreadTypeNames,6,num, 20, 5, 8, NRU);
    return 0;
}