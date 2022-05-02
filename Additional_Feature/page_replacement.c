
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0


/**************************************
 * The parameters of memory and disk pages 
 *
 * PageFrameList: The dynamically-allocated array representing memory pages
 * FrameNR: the number of page frames in memory
 * elementCount: Point to the next page to be replaced
 *
 * ReferenceString: The sequence of the demanding pages
 * ReferenceLength: The length of the randomized reference string
 * ReferenceSZ: the page number range in the reference string
 *
 */

#define ReferenceLength 20

typedef struct {
    int *PageFrameList;
    int elementCount;
}PageFrame;

int ReferenceSZ, FrameNR;

PageFrame memory;

int *ReferenceString;

FILE* output;


/* Test driver sub functions */

void generateReferenceString(unsigned int seed);

void initializePageFrame();

void printReferenceString();

void printPageFrame();

void runAlgos(int i);



/* Algorithm Functions */

int FIFO();

int LRU();

int CLOCK();

// others

/**
 * Returns the index of the given page.
 * @param page to look for
 * @return the index, -1 if not found
 */
int mem_index(int page);

/**
 * True iff page in memory
 * @param page to look for
 * @return
 */
int mem_contains(int page);

/*******************************
 *
 * The main function is the test driver for FIFO & LRU algorithms
 *
 * 1. Initialize the system parameters
 * 2. Initialize the memory pages 
 * 3. Generate the randomized reference string
 * 4. Apply the FIFO algorithm, calculate the number of page faults
 * 5. Apply the LRU algorithm, calculate the number of page faults
 */


int main(int argc, char* argv[]) {
    srand(time(NULL));

    if( argc != 3 ) {
        printf("Command format: Test <reference string size> <number of page frames>");
        exit(1);
    }

    ReferenceSZ = atoi(argv[1]);
    FrameNR = atoi(argv[2]);

    output = fopen("output", "w");

    for (int i = 0; i < 5; i++) {
        runAlgos(i);
    }

    return 0;

}

void runAlgos(int i) {
    generateReferenceString(time(NULL));

    fprintf(output, "Reference string: ");
    for (int i = 0; i < ReferenceLength; i++) {
        fprintf(output, "%d ", ReferenceString[i]);
    }
    fprintf(output, "\n");

    initializePageFrame();
    int fifo = FIFO();
    printf("page fault of FIFO: %d\n",fifo);
    fprintf(output, "page fault of FIFO: %d\n",fifo);
    free(memory.PageFrameList);

    printf("\n");
    printf("\n");

    printReferenceString();

    initializePageFrame();
    int lru = LRU();
    printf("page fault of LRU: %d\n",lru);
    fprintf(output, "page fault of LRU: %d\n",lru);

    printf("\n");
    printf("\n");

    printReferenceString();

    initializePageFrame();
    printPageFrame();
    int clock = CLOCK();
    printf("page fault of CLOCK:%d\n", clock);
    fprintf(output, "page fault of CLOCK:%d\n", clock);


    free(memory.PageFrameList);

    free(ReferenceString);

    fprintf(output, "\n");

}

/**********************************
 **********************************
 *
 * The test driver functions implmentation details
 *
 **********************************
 */

void generateReferenceString(unsigned int seed) {
    int i;
    //srand(seed);
    ReferenceString = (int *)malloc( sizeof(int) * ReferenceLength );
    printf("The randomized Reference String: ");

    for(i=0; i< ReferenceLength; i++) {
        ReferenceString[i] = rand() % ReferenceSZ;
        printf("%d ", ReferenceString[i]);
    }
    printf("\n");
}


void initializePageFrame() {
    int i;
    memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );
    memory.elementCount =0;
    for(i=0; i< FrameNR; i++) {
        memory.PageFrameList[i] = -1;
    }

}

void printPageFrame() {
    int i;
    for(i=0; i< FrameNR; i++) {
        printf("%2d ",memory.PageFrameList[i]);
    }
    printf("\n");
}

void printReferenceString() {
    int i;
    printf("The Same Reference String: ");
    for(i=0; i< ReferenceLength; i++) {
        printf("%d ", ReferenceString[i]);
    }
    printf("\n");

}




int FIFO() {
    int PagefaultCount = 0;
    Queue* queue = init_queue(FrameNR);

    printPageFrame();
    for (int i = 0; i < ReferenceLength; i++) {
        if(mem_contains(ReferenceString[i])) {
            // nothing to be done...
        } else if (mem_contains(-1)) {
            // load into memory
            int j = mem_index(-1);
            memory.PageFrameList[j] = ReferenceString[i];
            enqueue(queue, ReferenceString[i]);
        } else {
            // page fault
            PagefaultCount++;
            int to_be_replaced = dequeue(queue);
            int j = mem_index(to_be_replaced);
            memory.PageFrameList[j] = ReferenceString[i];
            enqueue(queue, ReferenceString[i]);
        }
        printPageFrame();
    }
    return PagefaultCount;
}



int LRU() {
    int PagefaultCount = 0;
    Queue* queue = init_queue(FrameNR);

    printPageFrame();
    for (int i = 0; i < ReferenceLength; i++) {
        if(mem_contains(ReferenceString[i])) {
            move_to_tail(queue, ReferenceString[i]);
        } else if (mem_contains(-1)) {
            // load into memory
            int j = mem_index(-1);
            memory.PageFrameList[j] = ReferenceString[i];
            enqueue(queue, ReferenceString[i]);
        } else {
            // page fault
            PagefaultCount++;
            int to_be_replaced = dequeue(queue);
            int j = mem_index(to_be_replaced);
            memory.PageFrameList[j] = ReferenceString[i];
            enqueue(queue, ReferenceString[i]);
        }
        printPageFrame();
    }
    printPageFrame();

    return PagefaultCount;

}

int CLOCK() {
    /* Pages get a random R value when enqueued to simulate memory access from outside */
    int PagefaultCount = 0;
    Queue* queue = init_queue();

    printPageFrame();
    for (int i = 0; i < ReferenceLength; i++) {
        if(mem_contains(ReferenceString[i])) {
            // nothing to be done...
        } else if (mem_contains(-1)) {
            // load into memory
            int j = mem_index(-1);
            memory.PageFrameList[j] = ReferenceString[i];
            enqueue(queue, ReferenceString[i]);
        } else {
            // page fault
            PagefaultCount++;


            // searching for an appropriate place, i.e. shifting the `hand'
            while(TRUE) {
                printf("Looking for a space\n");
                Node* to_be_replaced = dequeue_node(queue);

                int page = to_be_replaced->page;
                int R = to_be_replaced->R;
                if (R) {
                    to_be_replaced->R = FALSE;
                    enqueue(queue, page);
                    continue;
                } else {
                    // R = 0, so evict the page
                    int j = mem_index(page);
                    memory.PageFrameList[j] = ReferenceString[i];
                    enqueue(queue, ReferenceString[i]);
                    break;
                }
            }

        }
        //printPageFrame();
        print_queue(queue);
    }
    return PagefaultCount;
}


int mem_index(int page) {
    for (int i = 0; i < FrameNR; i++) {
        if (memory.PageFrameList[i] == page) return i;
    }
    return -1;
}

int mem_contains(int page) {
    return mem_index(page) != -1;
}

