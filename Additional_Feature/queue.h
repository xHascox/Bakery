typedef struct Node {
    sem_t customer_semaphore;
    struct Node* previous;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int nbElements;
} Queue;

Queue* init_queue();
void enqueue(Queue* q, sem_t customer_semaphore);
sem_t dequeue(Queue* q);
Node* dequeue_node(Queue* q);
void move_to_tail(Queue* q, int page);
Node* create_node(sem_t customer);
void print_queue(Queue* q);
int length(Queue* q);
