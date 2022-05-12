all: sleeping_baker

sleeping_baker: sleeping_baker.o queue.o
	gcc -pthread sleeping_baker.c queue.o -o sleeping_baker

queue.o: queue.c queue.h
	gcc -c queue.c