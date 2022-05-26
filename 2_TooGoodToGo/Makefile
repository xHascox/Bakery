default:	
	make precompile && gcc -Wall -pthread -o tgtg.o tgtg_new.c LL.o

precompile:
	gcc -Wall -o LL.o -c LinkedList.c

run:
	./tgtg.o

clean:
	rm *.o
	
rm:
	rm *.o
