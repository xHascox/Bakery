output: driver.o shop.o
	g++ -std=c++0x -Wall driver.o shop.o -o output

driver.o: driver.cpp
	g++ -c driver.cpp

shop.o: shop.cpp shop.h
	g++ -c shop.cpp

clean:
	rm *.o output