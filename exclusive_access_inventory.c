/*

Idea:
- Protect inventory from simultaneous access using a mutex.
- But: If several threads are waiting on the mutex, how do we enforce a certain order (i.e. arrival order)?
 --> Keep track of interested list. The teacher then wakes up the threads in order of arrival. 

*/



int main(){



    // Create threads/apprentices.




    return 0;
}