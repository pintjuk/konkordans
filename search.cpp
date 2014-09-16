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
char tolowcase(char b){
	if(((int)b) >= 65 && ((int)b) <= 90) b+=32;
	if(b == (char)0xC4) b=(char)0xE3;
	if(b == (char)0xD6) b=(char)0xF6;
	if(b == (char)0xC5) b=(char)0xE5;
	return b;
}
string tolowcase (string a){
	for (char& c: a)c=tolowcase(c);
	return a;
}
bool match_lowcase(char a, char b){
	return tolowcase(a)==tolowcase(b);
}

bool istermenateword(char b){
	return b<65||(b>90&&b<97)||b>122&&b!=196&&b!=107&&b!=214&&b!=228&&b!=229&&b!=246;
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
	bool highlite=false;
	if(argc == 3){
		if(string(argv[2])=="-c"){
			highlite = true;
		}
	}
	if (argc < 2 ) {
		cerr << "Ange en sökterm." << endl;
		exit(1);
	}
	string searchterm= tolowcase(string(argv[1]));
	cerr << "Sökt ord: " << searchterm << endl;

	int hash = latman(string(searchterm));
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

		if (word == searchterm) {
			cerr << "Level 2 -> Level 3 pointer: " << position << endl;
			break;
		}

	}

	level3_i_f.seekg(position);
	vector<int> matchpointers;
 	while (level3_i_f) {
		unsigned int pos;
		level3_i_f >> pos;
		
		if (pos == (unsigned int)-1) {
			
			break;
		}
		matchpointers.push_back(pos);

	}
	cout << "Hitade " << matchpointers.size() << " matchningar"<<endl;
	if(matchpointers.size()> 25){
		cout << "Vill du skriva ut resultat? (y/n)\n:";
		string svar;
		cin >> svar;
		if(svar!="y"){
			exit(0);
		}
	}

	for(int pos: matchpointers){
		
		int posless = (((int)pos-30) < 0)?0:pos-30;
		korpus.seekg(posless);	
		cout << "...";
		string matching_chars="";
		for(int i =0;i<60+ searchterm.length();i++){
			if(!korpus)exit(0);
			char lel;
			korpus.get(lel);
			if(lel=='\n')
				lel=' ';
			if(highlite){
				if(match_lowcase(searchterm[matching_chars.size()], lel)){
					matching_chars+=lel;
					if(matching_chars.size()==searchterm.size()&& istermenateword(korpus.peek())){
						cout << "\x1b[1m" << matching_chars << "\x1b[0m";
						matching_chars ="";
					}
				}else{
					cout << matching_chars << lel;
					matching_chars ="";
			}
			}else{
				cout << lel;
			}
		}
		cout<<"..." <<endl;
	}


	level3_i_f.close();
	level2_i_f.close();
	level1_i_f.close();
	korpus.close();

}
