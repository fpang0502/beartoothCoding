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
	//encode
	Manchester myParser;
	myParser.parse(mode, inputfile, outputfile);
	myParser.getMessage();
	return 0;
}


// bool encode(string inputfile, string outputfile){
// 	ifstream ifile;
// 	ifile.open(inputfile);
// 	ofstream ofile;
// 	ofile.open(outputfile);
// 	if(ifile.fail()) return false;
// 	if(ofile.fail()) return false;
	
// 	string line;
// 	while(getline(ifile, line)){
// 		stringstream ss(line);
// 		char c;
// 		ss >> noskipws;
// 		while(ss>>c){
// 			string binary = bitset<8>(c).to_string();
// 			cout << c << ": " << binary << " ";
// 			string manchester = binaryToManchester(binary);
// 			ofile << manchester;
// 		}
// 	}
	
// 	ifile.close();
// 	ofile.close();
// 	return true;
// }

// bool decode(string inputfile, string outputfile){
// 	ifstream ifile;
// 	ifile.open(inputfile);
// 	ofstream ofile;
// 	ofile.open(outputfile);
// 	if(ifile.fail()) return false;
// 	if(ofile.fail()) return false;
	
// 	string line;
// 	while(getline(ifile, line)){
// 		stringstream ss(line);
// 		for(unsigned int i=0; i<line.size(); i+=16){
// 			string binary;
// 			for(unsigned int j=i; j<i+16; j+=2){
// 				char bitOne = line[j];
// 				char bitTwo = line[j+1];
// 				string manchester;
// 				manchester += bitOne;
// 				manchester += bitTwo;
// 				if(manchester =="01"){
// 					binary += "1";
// 				}
// 				else if(manchester == "10"){
// 					binary += "0";
// 				}
// 			}
// 			char letter = bitset<8>(binary).to_ulong();
// 			cout << letter << endl;
// 			ofile << letter;
// 		}
// 		cout << endl;
// 	}
	
// 	ifile.close();
// 	ofile.close();
// 	return true;
// }

// string binaryToManchester(string s){
// 	string manchester;
// 	for(unsigned int i=0; i<8; i++){
// 		if(s[i]=='0'){
// 			manchester+="10";
// 		}
// 		else{
// 			manchester+="01";
// 		}
// 	}
// 	return manchester;
// }