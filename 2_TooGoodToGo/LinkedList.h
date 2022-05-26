#ifndef LL_TGTG
#define LL_TGTG

/**
 * @brief This is the main struct for the linked list. It stores the head node of the linked list \n
 * and some useful values such as the oldest bread, the recently sold bread, the total amout of sold bread \n
 * and the total amount of donated bread. 
 * 
 */
struct LinkedList {
    struct Node* head;      // Pointer to first Node in the LinkedList
    int oldestBread;        
    int recentlySold;       
    int totalSold;
    int totalDonated;
};
typedef struct LinkedList LinkedList;


LinkedList* newList();


void addNode(LinkedList* list, int t);


int removeNode(LinkedList* list);


int length(LinkedList* list);


#endif