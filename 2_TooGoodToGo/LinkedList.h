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


/**
 * @brief A new linked list struct is created and returned.
 * 
 * @return LinkedList* - Pointer to newly created LinkedList
 */
LinkedList* newList();


/**
 * @brief Created and adds a new Node with a timestamp 't' to the LinkedList. 
 * 
 * @param list Pointer to a LinkedList struct where a Node should be added to.
 * @param t The current timestamp
 */
void addNode(LinkedList* list, int t);


/**
 * @brief Removes the first node of the LinkedList provided and returns its timestamp.
 * 
 * @param list Pointer to a LinkedList struct where the first Node should be removed from.
 * @return int - The timestamp stored in the removed node.
 */
int removeNode(LinkedList* list);


/**
 * @brief Returns the lenght (amount of Nodes) of the provided LinkedList.
 * 
 * @param list Pointer to a LinkedList struct of which the length should be calculated.
 * @return int - Lenght of the LinkedList (amount of Nodes)
 */
int length(LinkedList* list);


#endif