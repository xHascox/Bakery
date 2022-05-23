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

Possible improvements:
* [x] Dynamic datastructure for ingredients
* [no] A way to test dynamic data structure.
* [] Testing script

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
* [x] Dynamic bread type addition
* [] Implement additional strategies (Extra)
* [] Testing script


# 3 Additional features

Sleeping Barber:

Pizza:

# Questions
* How to do testing (of the scenarios)? --> Use large numbers for apprentices.
* Do we have to compile everything in one file? --> No, but we can.
* Does the project count 30 or 40%? --> Answer: 30%
* Inventory:
  * Do the apprentices take all ingredients at once, or only one at once? --> Both options are okay.
  * Ines: Would be good to implement dynamic datatypes for ingredients.
  * In what way does the inventory have to be dynamic?
* TooGoodToGo
  * Is it okay to run the toogodtogo algorithm every k ticks, like paging, or should it be run only once (1 hour before the bakery closes)' --> Ines will send us an email --> Its okay to have k ticks.


# Todos
*  [DONE]: (i) Implement dynamic data structure for exercise 1 (Thirit; Sehr nice wäre, wenn du ein einen dynamischen Array implementieren könntest, der in jedem Index einen linked list hat. Damit könnte der user eine Zahl als input geben (bspw. 2 welches dann für Mehl stehen würde) und dann hätte man im index 2 des arrays eine linked list, in der jeder Node 1 kg Mehl darstellt. Jeder Node der linked list sollte eine ID enthalten, und die Linked List sollte die üblichen Funktionalitäten haben (append, remove, getLength, etc.).)
* (ii) (Re)implement ex.1 as an analogy to mutual exclusion on shared resources (Marco/Pablo). Implement scenarios.
* (iii) Implement CLI to start all the scripts and input parameters (Lukas). (TODO: add defualt values, restock all ingredients doenst qworkj, expose metric as CLI argument)
* (iv) Write testing scripts. (automated testing -> defualts (give "default" as comand arguemtn, then dont ask for inputs, chose defaults))
* (v) Code cleaning.
* (vi) Code commenting.
* (vii) Write documentation. (dont forget to comment about Nathans remark about the tgtg baskets, dont forget scenarios)
* (viii) Prepare presentation.
* (ix) Upload stuff to gitlab.

Log: 
22.5 added mutex to shopper
Welche metric als default?
Todo: Code Comments, Cleaning, Default testing scripts, restocking

Wee möchemer das mit de testing scripts, nur 1 cli, aber denn alli fodlers zu eim? oder wtf?
d default testings mömmer zeme merge, im MakingBread heds d autoMakeBread funcntion, im AddFeature die für sleeping
Speicherzugriffsfehler wenn ich maing bread ./mainn.o 1
mache ganz am schluss, lol wtf?

In CLI muss noch metric exposed werden.
In baker() muss noch metric implementiert werden. Können wir "scenarios" löschen?
Doctypes in allen files (ausser BinaryTree)
Output von exclusive access noch clean machen.
Too good to go ist sehr minimal
What about testing scripts?