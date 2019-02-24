#include <iostream>
#include "Manchester.h"

using namespace std;

int main(int argc, char* argv[]){
	// take in 3 arguments -d/-e inputfile outputfile
	if(argc < 4) {
		cout << "Not enough arguments." << endl;
		return 0;
	}
	string mode = argv[1];
	string inputfile = argv[2];
	string outputfile = argv[3];
	//instantiate a Manchester parser
	Manchester myParser;
	// parse with the mode, input and output given
	myParser.parse(mode, inputfile, outputfile);
	// print the message after parsing
	myParser.getMessage();
	return 0;
}