default:	
	gcc -pthread -o makeBreadEx.o exclusive_access_inventory.c Inventory_BinTree.c
precompile:
	gcc -Wall -o BinTreeInv.o -c Inventory_BinTree.c && gcc -Wall -o RecipeBook.o -c Recipe_Book.c && gcc -Wall -o ExclAccInv.o -c exclusive_access_inventory.c
cli:
	gcc -pthread -o	testCli.o cli.c ExclAccInv.o BinTreeInv.o RecipeBook.o
run:
	./makeBreadEx.o
runCli:
	./testCli.o
clean:
	rm *.o rm
rm:
	rm *.o
