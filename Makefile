flags = -std=c++11 -O2 -g -Wall

indexer: indexer.o
	g++ $(flags) indexer.o -o indexer 
indexer.o: indexer.cpp latmanshash.hpp
	g++ $(flags) -c indexer.cpp
search: search.o
	g++ $(flags) search.o -o search
search.o: search.cpp latmanshash.hpp
	g++ $(flags) -c search.cpp
clean:
	rm *.o indexer  search
clean_crap:
	rm level1 level2 level3