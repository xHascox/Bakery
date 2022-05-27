# HOW TO RUN THE BAKERY:

run the "make" command in the root directory

## Manual Testing

Run ./main.o and you are guided through by the program interface.

## Automated Testing

Example: ./main.o 1 3 1 

This will run the testing script of Making Bread with "Pre Learners" as the scheduling emtric and sleeps deactivated

### 1 Making Bread

SYNTAX: ./main.o X [Y] [[Z]]

    // X = 1 // Making Bread

    // Y = 0 // Fairlearners
    // Y = 1 // Fastlearners
    // Y = 2 // Arrivalorder
    // Y = 3 // Default, Prelearners (called fast learners in the project description)
    // Y = 4 // Scenario 2

    // Z = 0 // Slow test, the apprentices take some time to make bread, so the prints are printed slowly
    // Z = 1 // Default, Fast test, so the apprentices bake bread as fast as they can, so the end statistics can be seen without waiting forever

Default Values used: 

    - Apprentices                 1000
    - Target number of Breads     10000
    - Inventory Stock             20
    - Number of Breadtypes        1
    - Number of Ingredients       1
    - Scheduling metric           3 (pre learners) [Y]
    - fast                        1 (sleep deactivated) [Z]


### 2 Too Good To Go

SYNTAX: ./main.o X [Y]

        // X = 2 // Too Good To Go

        // Y = 0 // FIFO
        // Y = 1 // Second Chance
        // Y = 2 // NRU

### 3 Additional Feature

SYNTAX: ./main.o X [Y] [[Z]]

        // X = 3 // Additional Feature Sleeping Baker
        
        // Y = Number of Customers

        // Z = Number of Chairs


## Important Keywords / Glossary

#### Making Bread: metric

This parameter changes on which premise the baker allows apprentices to access the inventory.

- Fair Learners: Schedule the apprentice with the smallest number of breads he has already made first
- Fast Learners: Schedule the apprentice with the largest number of breads he has already made first
- Arrival Order: Schedule the apprentice that arrived first (using timestamps)
- Pre Learners: Schedule according to a predefined order (Apprentice IDs)





