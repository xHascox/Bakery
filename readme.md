![image](https://user-images.githubusercontent.com/54436086/167746566-c6555442-a760-4756-b7bf-ab1019a806ea.png)

### new_main.c 

Because POSIX signals are subject to Race-Conditions (the pthread_cond_signal is lost, if the receiving thread is not yet blocking on pthread_cond_wait), we had to use Semaphores.
The value of Semaphores is long-living 

<img src="https://cdn.prod.www.manager-magazin.de/images/4467ecb4-8989-49ff-8dee-db7e8ca97493_w948_r1.778_fpx56.31_fpy50.jpg" alt="Jack Daniels" style="height: 100px;"/>



Maybe, JUST MAYBE, should we protect the Queue of our Chairs with a mutex?
