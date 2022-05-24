#ifndef Q_SB
#define Q_SB


/**
 * @brief A Node stores one customer's semaphore and a pointer to the previous and next node respectively.
 * 
 */
typedef struct Node {
    sem_t* customer_semaphore;  // The sutomer's semaphore
    struct Node* previous;      
    struct Node* next;
} Node;


/**
 * @brief A Queue struct contains a pointer to the 'head' and 'tail' node and the number of nodes enqueued.
 * 
 */
typedef struct {
    Node* head;         // First node of the queue
    Node* tail;         // Last node ofthe queue
    int nbElements;     // Number of taken chairs
} Queue;


/**
 * @brief Initializes a new queue and returns it.
 * 
 * @return Queue* 
 */
Queue* init_queue();


/**
 * @brief Puts a with the passed arguments newly created node into the queue. \n
 * 
 * @param q Pointer to a queue to enqueue on.
 * @param customer_semaphore The customer's specific semaphore with which one can wake the customer up.
 */
void enqueue(Queue* q, sem_t* customer_semaphore);


/**
 * @brief Get the first element's semaphore and delete/free the respective node afterwards. \n
 * 
 * @param q Pointer to a queue to dequeue on.
 * @return sem_t* 
 */
sem_t* dequeue(Queue* q);


/**
 * @brief Return length of Queue
 * 
 * @param q Pointer to a queue to get the lenght of. 
 * @return int 
 */
int length(Queue* q);



#endif