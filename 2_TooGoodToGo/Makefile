default:	
	gcc -Wall -o tgtg.o cli.c toogood.o linkedlist.o && make precompile

precompile:
	gcc -Wall -o linkedlist.o -c linkedlist.c && gcc -Wall -o toogood.o -c toogood.c

run:
	./tgtg.o

clean:
	rm *.o
	
rm:
	rm *.o
