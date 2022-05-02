all: sleeping_baker.c queue.o queue.h
	gcc -pthread sleeping_baker.c queue.o -o sleeping_baker

queue.o: queue.c queue.h
	gcc -c queue.c