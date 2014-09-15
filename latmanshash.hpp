#ifndef LATMAN_H
#define LATMAN_H
#include <string>
using namespace std;
int latman(string i){
	const char* identifier = i.c_str();
	int hash=0;
	int mult = 1;
	for(int i = 0; i <3; i++){

		if(identifier[i]=='\0'){
			return hash;
		}
		switch (identifier[i]){
			case (char)0xf6: /* ö */
				hash += 29 * mult;
				break; 
			case (char)0xe5: /* å */
				hash += 27 * mult;
				break;
			case (char)0xe4: /* ä */
				hash += 28 * mult;
				break;
			default:
				hash += (identifier[i]-96) * mult;
				break;
		}

		mult*=30;
	}
	return hash;
}
#endif /* LATMAN_H */
