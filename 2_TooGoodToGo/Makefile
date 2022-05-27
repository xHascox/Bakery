default:	
	make precompile && gcc -pthread -o	tgtg.o cli.c LL.o tgtgPre.o

precompile:
	gcc -Wall -o LL.o -c LinkedList.c && gcc -Wall -pthread -o tgtgPre.o -c tgtg.c LL.o

run:
	./tgtg.o

clean:
	rm *.o
	
rm:
	rm *.o
