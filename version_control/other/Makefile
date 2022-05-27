default:	
	gcc -pthread -o testing1.o testing1.c && gcc -pthread -o	./1_MakingBread/main.o ./1_MakingBread/cli.c ./1_MakingBread/ExclAccInv.o ./1_MakingBread/BinTreeInv.o ./1_MakingBread/RecipeBook.o && make precompile

precompile:
	gcc -Wall -o ./1_MakingBread/BinTreeInv.o -c ./1_MakingBread/Inventory_BinTree.c && gcc -Wall -o ./1_MakingBread/RecipeBook.o -c ./1_MakingBread/Recipe_Book.c && gcc -Wall -o ./1_MakingBread/ExclAccInv.o -c ./1_MakingBread/exclusive_access_inventory.c

run:
	./main.o

clean:
	rm *.o rm

rm:
	rm *.o
