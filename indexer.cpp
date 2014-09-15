#include <iostream>
#include "latmanshash.hpp"
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;
typedef unordered_map<string,vector<uint32_t>> pindex; 

void openfstream(fstream& filestream, ios_base::openmode flags){
	filestream.open("index", flags);
	if(!filestream.is_open()){
		cerr << "faild to open file" << endl;
		exit(1);
	}
}

int main(void) {
	pindex pindex;
	fstream level3_i_f;
	fstream level2_i_f;
	fstream level1_i_f;

	unordered_map<string, uint32_t> level3_positions; 
	openfstream(level3_i_f, fstream::out| fstream::app);
	openfstream(level2_i_f, fstream::out| fstream::app);
	openfstream(level1_i_f, fstream::out| fstream::app);
	//fseek(file, 10000, SEEK_SET);
	
	while(cin){
		char word[45];
		uint32_t pointer;
		cin.getline(word, 45, ' ');
		cin >> pointer;
		cin.get();
		pindex[word].push_back(pointer);
	}

	for (auto i : pindex) {
		level3_positions[i.first] = level3_i_f.tellp();
		for(uint32_t n : i.second) {
			//level3_i_f.write((char*)&n, sizeof(n));
			level3_i_f << n << endl;
		}
		
	}

	cout << "Size: " << pindex.size() << "\n";
	level3_i_f.close();
	level2_i_f.close();
	level1_i_f.close();
	return 0;
}
