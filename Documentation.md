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
* Bread :: struct containing int representing the bread type. E.g., 1 == croissant, 2 == zopf.
* TypeTimestamp :: Array of bool length n containing most recent selling time for each bread type. Gets reset after k ticks.
* k :: int representing the number of ticks until TypeTimestamp is set to false for all the entries.

Structure of code:
* Three phases in the code: (1) Production phase (bake breads), (2) Sell breads, (3) TGTG decision.


# 3 Additional features
