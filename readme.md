### new_main.c 

Because POSIX signals are subject to Race-Conditions (the pthread_cond_signal is lost, if the receiving thread is not yet blocking on pthread_cond_wait), we had to use Semaphores.
The value of Semaphores is long-living 
