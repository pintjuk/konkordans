#include <iostream>
#include "latmanshash.hpp"
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>

using namespace std;
typedef unordered_map<string,vector<uint32_t>> pindex; 

void openfstream(fstream& filestream, ios_base::openmode flags, string name){
	filestream.open(name, flags);
	if(!filestream.is_open()){
		cerr << "failed to open file" << endl;
		exit(1);
	}
}

int main(int argc, char ** argv) {

	if (argc == 2) {
		cout << latman(string(argv[1])) << endl;
		exit(0);
	}

	pindex pindex;
	fstream level3_i_f;
	fstream level2_i_f;
	fstream level1_i_f;
	map<string, uint32_t> level3_positions;
	unordered_map<int, uint32_t> level2_positions;
	openfstream(level3_i_f, fstream::out| fstream::app, "level3");
	openfstream(level2_i_f, fstream::out| fstream::app, "level2");
	openfstream(level1_i_f, fstream::out, "level1");
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
		//cout << i.first << endl;
		for(uint32_t n : i.second)
			level3_i_f << n << endl;
		level3_i_f << (unsigned int)-1 << endl;
		
	}
	
	for (auto i : level3_positions) {
		if(!level2_positions.count(latman(i.first))){
			cout<< "level3    :" << latman(i.first) << " " << i.first << endl; 
			level2_positions[latman(i.first)]=level2_i_f.tellp();
		}
		
		level2_i_f << i.first << endl << i.second << endl;
	}

	for (auto i : level2_positions){
 		level1_i_f.seekp(i.first*4);
		level1_i_f.write((char*)&i.second, 4);
		cout << i.first*4 << " " << i.second <<endl;
	}

	cout << "Size: " << pindex.size() << "\n";
	level3_i_f.close();
	level2_i_f.close();
	level1_i_f.close();
	return 0;
}
