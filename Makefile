flags = -std=c++11 -O2 -g

indexer: indexer.o
	g++ $(flags) indexer.o -o indexer 
indexer.o: indexer.cpp latmanshash.hpp
	g++ $(flags) -c indexer.cpp
clean:
	rm *.o indexer 