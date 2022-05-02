typedef struct Node {
    int page;
    int R;
    struct Node* previous;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int nbElements;
} Queue;

Queue* init_queue();
void enqueue(Queue* q, int page);
int dequeue(Queue* q);
Node* dequeue_node(Queue* q);
void move_to_tail(Queue* q, int page);
Node* create_node(int page, int R);
void print_queue(Queue* q);
