default:	
	gcc -pthread -o main.o main.c
run:
	./main.o
clean:
	rm *.o
rm:
	rm *.o
