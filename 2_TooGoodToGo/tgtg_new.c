#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>

// Readability
#define NO 0
#define YES 1

// Paging Algorithms
int strategy;
#define FIFO 0
#define SecondChance 1
#define NRU 2

// Global Variables
char **BreadTypeNames;
int *RecentlySold;
int NBBreadTypes;
struct LinkedList **Breads;
int BreadsToSell;
int BreadsSold;
int ticks;
int grace_period;
int *BreadAmounts;
int tgtg_flag;
pthread_t tgtg_coordinator;
pthread_mutex_t mutTGTGFlag;

// Functions
void bakeBreads(struct LinkedList* BreadType, int amount, int timestamp);
void *tgtg_coordinate();
void tgtg(int strategy, int timestamp);
void fifo(int timestamp);
void secondchance(int timestamp);
void nru(int timestamp);
void sellBread(int timestamp);
void runTGTG(char** names, int nbTypes, int* amounts, int max, int t, int p, int s);

struct LinkedList {
    struct Node* head;
    int oldestBread;
    int recentlySold;
    int totalSold;
    int totalDonated;
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
    list->totalSold = 0;
    list->totalDonated = 0;
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
        sleep(ticks);
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

    for(int i = 0; i < NBBreadTypes; i++){
        struct LinkedList* BreadType = Breads[i];
        BreadType->recentlySold = NO;
    }
}

void fifo(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        struct LinkedList* BreadType = Breads[i];
        int donate_counter = 0;
        while(BreadType->oldestBread >= timestamp - grace_period){ // Donate bread that is older than two ticks
            donate_counter += 1;
            removeNode(BreadType);
        }
        BreadType->totalDonated += donate_counter;
        printf("We donated %d %ss\n", donate_counter, BreadTypeNames[i]);
    }
}

void secondchance(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        struct LinkedList* BreadType = Breads[i];
        if(BreadType->oldestBread >= timestamp - grace_period){
            if(BreadType->recentlySold == NO){
                int donate_counter = 0;
                while(BreadType->oldestBread >= timestamp - grace_period){ // Donate bread that is older than two ticks
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

void nru(int timestamp){
    for (int i = 0; i < NBBreadTypes; i++){
        struct LinkedList* BreadType = Breads[i];
        if(BreadType->recentlySold == NO){
            int donate_counter = 0;
            while(BreadType->oldestBread >= timestamp - grace_period){ // Donate bread that is older than two ticks
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

void sellBread(int timestamp){
    int type = rand() % NBBreadTypes;
    struct LinkedList *BreadType = Breads[type];
    if (length(BreadType) > 0){
        int timestamp = removeNode(BreadType);
        BreadType->recentlySold = YES;
        BreadType->totalSold += 1;
        printf("A bread was sold! Type: %s\n", BreadTypeNames[type]);
    } else {
        printf("Unfortunately there is no more %s left. We will bake some more.\n", BreadTypeNames[type]);
        bakeBreads(BreadType, BreadAmounts[type], timestamp);
        int timestamp = removeNode(BreadType);
        BreadType->recentlySold = YES;
        BreadType->totalSold += 1;
        printf("A bread was sold! Type: %s\n", BreadTypeNames[type]);
    }
}

void runTGTG(char** names, int nbTypes, int* amounts, int max, int t, int p, int s) {

    /* INITIALIZE VARIABLES BASED ON USER INPUT */
    BreadTypeNames = names;
    NBBreadTypes= nbTypes;
    BreadAmounts = amounts;
    Breads = malloc(sizeof(struct LinkedList*)*NBBreadTypes);
    RecentlySold = malloc(sizeof(int)*NBBreadTypes);
    ticks = t;
    strategy = s;
    BreadsSold = 0;
    tgtg_flag = NO;
    BreadsToSell = max;
    grace_period = p;

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
            printf("----------------------------\n");
            printf("Time to take a TGTG decision:\n");
            tgtg_flag = NO;
            tgtg(strategy,BreadsSold);
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

    return;
}


int main(int argc, char const *argv[]){
    char* BreadTypeNames[] = {"Croissant", "Zopf", "Tessinerli", "Bli", "Bla", "Blu"};
    int num[6] = {3,3,3,3,3,3}; 
    runTGTG(BreadTypeNames,6,num, 20, 5, 8, NRU);
    return 0;
}