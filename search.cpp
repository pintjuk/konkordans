#include <iostream>
#include "latmanshash.hpp"
#include <unordered_map>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

void openfstream(fstream& filestream, ios_base::openmode flags, string name){
	filestream.open(name, flags);
	if(!filestream.is_open()){
		cerr << "failed to open file" << endl;
		exit(1);
	}
}

int main(int argc, char ** argv) {
	fstream level3_i_f;
	fstream level2_i_f;
	fstream level1_i_f;

	openfstream(level3_i_f, fstream::in, "level3");
	openfstream(level2_i_f, fstream::in, "level2");
	openfstream(level1_i_f, fstream::in, "level1");


	if (argc != 2) {
		cout << "Ange en sökterm." << endl;
		exit(1);
	}

	cout << "Sökt ord: " << argv[1] << endl;

	int hash = latman(string(argv[1]));
	cout << "Hash: " << hash << endl;

	level1_i_f.seekg(hash*4);
	char level1_selected_c[4];

	level1_i_f.read(level1_selected_c, 4);
	uint32_t level1_selected_i = *(int *) level1_selected_c;

	cout << "Level 1 -> Level 2 pointer: " << level1_selected_i << endl;

	level2_i_f.seekg(level1_selected_i);

	uint32_t position;
 	for (;;) {
		string word;
		level2_i_f >> word;
		level2_i_f >> position;
		cout << "Trying match: " << word << endl;
		if (latman(word) != hash) {
			cout << "Ingen matchning hittad (" << hash << "," << latman(word) << ")" << endl;
			exit(0);
		}

		if (word == string(argv[1])) {
			cout << "Level 2 -> Level 3 pointer: " << position << endl;
			break;
		}

	}

	level3_i_f.seekg(position);
 	for (;;) {
		uint32_t pos;
		level3_i_f >> pos;
		cout << "Location in Korpus: " << pos << endl;

		if (pos == (unsigned int)-1) {
			cout << "No more matches" << endl;
			break;
		}

	}


	level3_i_f.close();
	level2_i_f.close();
	level1_i_f.close();

}
