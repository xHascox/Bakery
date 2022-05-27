#ifndef SLEEPING_B
#define SLEEPING_B


/**
 * @brief This is the main run-function of the additional feature (sleeping baker). \n
 * It takes in the required arguments and declares some local variables with them. \n
 * Then the queue and the semaphore array are created and initialized. After that, the customers and baker threads are also created. \n
 * Lastly, the threads are joined.
 * 
 * @param nbcustomers Amount of customers to be served.
 * @param nbchairs Amount of free places for a customer to sit in.
 */
void runAddF(int nbcustomers, int nbchairs);



#endif
