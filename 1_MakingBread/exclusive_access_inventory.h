#ifndef EXCL_ACC_INV
#define EXCL_ACC_INV

/**
 * @brief 
 * 
 * @param nbAppr 
 * @param maxB 
 * @param nbIngr 
 * @param ingNames 
 * @param nbBT 
 * @param breadNamesArr 
 * @param metric 
 * @param scen 
 */
void runMakingBread (int nbAppr, int maxB, int* nbIngrArr, char*** ingNames, int stock, int nbBT, char** breadNamesArr, int metric, int scen);

#endif