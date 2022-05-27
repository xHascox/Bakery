default: 
	make precompile && gcc -Wall -pthread -o bakery.o cli.c ./1_MakingBread/BinTreeInv.o ./1_MakingBread/RecipeBook.o ./1_MakingBread/ExclAccInv.o ./2_TooGoodToGo/LL.o ./2_TooGoodToGo/tgtgPre.o ./Additional_Feature/queue.o ./Additional_Feature/sleeping_baker.o

precompile:
	make precompMB && make precompTGTG && make precompAddF

precompMB:
	(cd ./1_MakingBread && gcc -Wall -o BinTreeInv.o -c Inventory_BinTree.c && gcc -Wall -o RecipeBook.o -c Recipe_Book.c && gcc -Wall -o ExclAccInv.o -c exclusive_access_inventory.c)
	
precompTGTG:
	(cd ./2_TooGoodToGo && gcc -Wall -o LL.o -c LinkedList.c && gcc -Wall -pthread -o tgtgPre.o -c tgtg.c LL.o)

precompAddF:
	(cd ./Additional_Feature && gcc -Wall -o queue.o -c queue.c && gcc -pthread -Wall -o sleeping_baker.o -c sleeping_baker.c)

run:
	./bakery.o

clean:
	(cd ./1_MakingBread && make rm)
	(cd ./2_TooGoodToGo && make rm)
	(cd ./Additional_Feature && make rm)
	rm *.o 

rm:
	(cd ./1_MakingBread && make rm)
	(cd ./2_TooGoodToGo && make rm)
	(cd ./Additional_Feature && make rm)
	rm *.o 
