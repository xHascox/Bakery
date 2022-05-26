#ifndef LL_TGTG
#define LL_TGTG

/**
 * @brief 
 * 
 */
struct LinkedList {
    struct Node* head;
    int oldestBread;
    int recentlySold;
    int tgtgBasket;
};
typedef struct LinkedList LinkedList;


LinkedList* newList();


void addNode(LinkedList* list, int t);


int removeNode(LinkedList* list);


int length(LinkedList* list);


#endif