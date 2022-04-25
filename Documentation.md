# 1 Learning to make bread

Goal: Ensure (i) that there is no deadlock and (ii) that no apprentice starves.

Analogy to: Scheduling.

## Possible strategies:
* Arrival order: No analogy to any scheduling algorithm (right?).
* Fast learners: Analogy to priority scheduling.
* Step-by-Step: Analogy to Round-Robin.
* --> We implement Round-Robin.

## Implementation of Round-Robin:

Variables:
* N :: int :: Number of apprentices
* MAX_A :: int :: Max. number of apprentices
* MAX_BREAD :: int :: Max number of bread to be produced
* mutA :: pthread_mutex_t :: 

# 2 Too good to go

Goal: Donate bread that is not going to be requested.

Analogy to: Page eviction.

## Possible strategies:
* Donate old bread: Analogy to FIFO.
* Second chance: Analogy to Second Chance.
* Not recently sold: Analogy to NRU.
* --> We implement NRU.

## Implementation of NRU:
Variables:
* Bread_Types :: struct containing int representing the bread type. E.g., 1 == croissant, 2 == zopf.
* types :: Array of Bread_Types :: Containing bread types the bakery offers.
* Sold :: Array of int::  Flags whether the bread type was sold in the last k TICKS.
* TICKS :: int representing the number of ticks until Sold is set to false for all the entries.
* TgtgBasket :: Array of int :: Flag for each bread type indicating whether the bread is offered via TGTG.

Structure of code:
* Three phases in the code: (1) Production phase (bake breads), (2) Sell breads, (3) TGTG decision.

Possible improvements:
* Dynamic bread type addition.
* Implement additional strategies.


# 3 Additional features
