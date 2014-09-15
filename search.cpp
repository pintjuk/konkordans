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
	fstream korpus;

	openfstream(level3_i_f, fstream::in, "level3");
	openfstream(level2_i_f, fstream::in, "level2");
	openfstream(level1_i_f, fstream::in, "level1");
	openfstream(korpus, fstream::in, "korpus");

	if (argc != 2) {
		cerr << "Ange en sökterm." << endl;
		exit(1);
	}

	cerr << "Sökt ord: " << argv[1] << endl;

	int hash = latman(string(argv[1]));
	cerr << "Hash: " << hash << endl;

	level1_i_f.seekg(hash*4);
	char level1_selected_c[4];

	level1_i_f.read(level1_selected_c, 4);
	uint32_t level1_selected_i = *(int *) level1_selected_c;

	cerr << "Level 1 -> Level 2 pointer: " << level1_selected_i << endl;

	level2_i_f.seekg(level1_selected_i);

	uint32_t position;
	string word;
 	for (;;) {
		
		level2_i_f >> word;
		level2_i_f >> position;
		cerr << "Trying match: " << word << endl;
		if (latman(word) != hash) {
			cerr << "Ingen matchning hittad (" << hash << "," << latman(word) << ")" << endl;
			exit(0);
		}

		if (word == string(argv[1])) {
			cerr << "Level 2 -> Level 3 pointer: " << position << endl;
			break;
		}

	}

	level3_i_f.seekg(position);
 	for (;;) {
		uint32_t pos;
		level3_i_f >> pos;
		if (pos == (unsigned int)-1) {
			cerr << "No more matches" << endl;
			break;
		}
		//cerr << "Location in Korpus: " << pos << endl;
		int posless = (((int)pos-30) < 0)?0:pos-30;
		korpus.seekg(posless);
		cout << "...";
		for(int i =0;i<60+word.length();i++){
			if(!korpus)exit(0);
			char lel;
			korpus.get(lel);
			if(lel=='\n')
				lel=' ';
			cout << lel;
		}
		cout <<"..."<< endl;

	}


	level3_i_f.close();
	level2_i_f.close();
	level1_i_f.close();
	korpus.close();

}
