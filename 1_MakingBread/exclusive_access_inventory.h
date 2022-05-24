#ifndef EXCL_ACC_INV
#define EXCL_ACC_INV


/**
 * @brief This is the main run function of 'learning to make bread' being passed all the necessary arguments. \n
 * First the function arguments are stored into local variables. Then, the recipe book and the invcentory are created. \n
 * Thirdly, the mutex, semaphore and index array for the apprentices are malloc'ed and initialized. \n
 * After that, the threads (baker, shopper, and the apprentices) are created  ans start their operation. \n
 * Lastly, after having baked enough breads, all the threads are joined together and some memory is freed.
 * 
 * @param nbAppr Number of apprentices
 * @param maxB The total amount of bread to be baked
 * @param nbBT Number of bread types
 * @param breadNamesArr Array for each bread type's name
 * @param nbIngrArr An array of int specifying the amount of ingredients each bread type needs; the index corresponds to the different bread types
 * @param ingNames An array with size equal to the number of bread types, pointing to the amount of ingredients (strings) each bread type has.
 * @param stonks Amount of initial stock and 'restockTo'-value
 * @param metric Chosing scheduling algorithm for 'learning to make bread'
 * @param scen The second scenario an be acivated by entering the specific value (2)
 */
void runMakingBread (int nbAppr, int maxB, int nbBT, char** breadNamesArr, int* nbIngrArr, char*** ingNames, int stonks, int metric, int scen);



#endif