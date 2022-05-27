#ifndef TGTG_RUN
#define TGTG_RUN

/**
 * @brief First the local variables, the mutex and the tgtg-coordinator thread are initialized. 
 * Secondly, the necessary breads are baked. After that, the selling if bread is stared. 
 * Lastly, the thread is joined and a summary is printed.
 * 
 * @param names Array of strings (char*) with names of bread types
 * @param nbTypes Number of bread types
 * @param amounts Array of int for each bread type specifying the amount of breads to be baked  and subsequently sold
 * @param max Amount of breads to sell
 * @param _ticks Amount of ticks to wait between each run of an algorithm
 * @param _grace_period Amount of ticks to wait until bread is donated
 * @param _strategy Strategy definign which algorithm to use
 */
void runTGTG(char** names, int nbTypes, int* amounts, int max, int _ticks, int _grace_period, int _strategy);

#endif