#include <iostream>
#include "latmanshash.hpp"
#include <stdio.h>
#include <unordered_map>
#include <vector>

using namespace std;
typedef unordered_map<string,vector<uint32_t>> pindex; 

FILE * openIndex(string name) {
	FILE * file;
	file = fopen(name.c_str(), "w");
	if (file == NULL) {
		cerr << "Unable to open index for writing\n";
		exit (1);
	}
	return file;
}

int main(void) {
	pindex pindex;
	FILE * file = openIndex("index");
	//fseek(file, 10000, SEEK_SET);
	

	while(cin){
		char word[45];
		uint32_t pointer;
		cin.getline(word, 45, ' ');
		cin >> pointer;
		cin.get();
		pindex[word].push_back(pointer);
	}

	cout << "Size: " << pindex.size() << "\n";

	return 0;
}
