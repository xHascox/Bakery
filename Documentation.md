# 1 Learning to make bread


# 2 Too good to go
Goal: Donate bread that is not going to be requested.

Analogy to: Page eviction.

## Possible strategies:
* Donate old bread: Analogy to FIFO.
* Second chance: Analogy to Second Chance.
* Not recently sold: Analogy to NRU.
* --> We implement NRU

## Implementation of NRU:
Variables:
* Bread :: struct containing int representing the bread type. E.g., 1 == croissant, 2 == zopf.
* TypeTimestamp :: Array of bool length n containing most recent selling time for each bread type.
* k :: int representing the number of iterations until TypeTimestamp is set to false for all the entries.

Structure of code:
* Three phases in the code: (1) Production phase (bake breads), (2) Sell breads, (3) TGTG decision.


# 3 Additional features