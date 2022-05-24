default:
	 make precompile && gcc -pthread -Wall -o main.o cli.c sleeping_baker.o queue.o

precompile:
	gcc -Wall -o queue.o -c queue.c && gcc -pthread -Wall -o sleeping_baker.o -c sleeping_baker.c

sleeping_baker: sleeping_baker.o queue.o
	gcc -pthread sleeping_baker.c queue.o -o sleeping_baker

queue.o: queue.c queue.h
	gcc -c queue.c

run:
	./main.o

clean:
	rm *.o

rm:
	rm *.o	