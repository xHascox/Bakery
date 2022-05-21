default:	
	gcc -pthread -o	main.o cli.c ExclAccInv.o BinTreeInv.o RecipeBook.o && make precompile

precompile:
	gcc -Wall -o BinTreeInv.o -c Inventory_BinTree.c && gcc -Wall -o RecipeBook.o -c Recipe_Book.c && gcc -Wall -o ExclAccInv.o -c exclusive_access_inventory.c

run:
	./main.o

clean:
	rm *.o rm

rm:
	rm *.o
