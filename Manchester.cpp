#include <iostream>
#include <sstream>
#include <bitset>
#include "Manchester.h"

using namespace std;

// Constructor
Manchester::Manchester(){
	this->errorMessage = "There is nothing wrong!\n";
	this->success=true;
}

// Destructor
Manchester::~Manchester()
{

}

// Get the message and print it
void Manchester::getMessage(){
	cout << this->errorMessage << endl;
}

// parse the input file and write an output
// takes in -d for decoding
// takes in -e for encoding
bool Manchester::parse(std::string mode, std::string inputfile, std::string outputfile){
	// open in the input and output files
	ifstream ifile;
	ifile.open(inputfile);
	ofstream ofile;
	ofile.open(outputfile);
	// throw error messages if failed
	if(ifile.fail()) {
		this->success = false;
		this->errorMessage = "Could not open inputfile.\n";
	}
	if(ofile.fail()) {
		this->success = false;
		this->errorMessage = "Could not open outputfile.\n";
	}
	if(success){
		//encode
		if(mode == "-e"){
			this->encode(ifile, ofile);
			if(this->success) return true;
		}
		//decode 
		else if(mode == "-d"){
			this->decode(ifile, ofile);
			if(this->success) return true;
		}
		// invalid parameter
		else {
			this->success = false;
			this->errorMessage = "Invalid parameter. Expected -e for encoding or -d for decoding.\n";
		}
	}
	// print the message
	this->getMessage();
	return false;
}

// encoding with input and output streams
void Manchester::encode(ifstream& ifile, ofstream& ofile){
	string line;
	// get each line
	while(getline(ifile, line)){
		stringstream ss(line +"\n");
		char c;
		// include whitespace to be parsed to manchester
		ss >> noskipws;
		while(ss>>c){
			// convert each character to binary string
			string binary = bitset<8>(c).to_string();
			// convert each binary string to manchester string
			string manchester = binaryToManchester(binary);
			// if it fails, return
			if(!this->success){
				ifile.close();
				ofile.close();
				return;
			}
			// write to the file
			ofile << manchester;
		}
	}
	// success
	ifile.close();
	ofile.close();
	this->success = true;
	this->errorMessage = "Finished encoding!\n"; 
}

// decode with input and output streams
void Manchester::decode(ifstream& ifile, ofstream& ofile){
	string line;
	// decode each line
	while(getline(ifile, line)){
		stringstream ss(line);
		// take in 16 bits at a time for each character
		for(unsigned int i=0; i<line.size(); i+=16){
			string binary;
			// convert each 16 bits to binary
			for(unsigned int j=i; j<i+16; j+=2){
				binary += this->manchesterToBinary(line[j], line[j+1]);
				if(!this->success){
					ifile.close();
					ofile.close();
					return;
				}
			}
			// convert each binary to character
			char letter = bitset<8>(binary).to_ulong();
			// write to output
			ofile << letter;
		}
	}
	// success
	ifile.close();
	ofile.close();
	this->success = true;
	this->errorMessage = "Finished decoding!\n"; 
}

// convert 8 bit binary to 16 bit manchester
// uses IEEE standard
string Manchester::binaryToManchester(string s){
	string manchester;
	for(unsigned int i=0; i<8; i++){
		if(s[i]=='0'){
			manchester+="10";
		}
		else if(s[i]=='1'){
			manchester+="01";
		}
		else {
			this->success = false;
			this->errorMessage = "Could not convert " + s + " to manchester.\n";
		}
	}
	return manchester;
}

// Converts a single manchester pair into its binary counterpart
string Manchester::manchesterToBinary(char b1, char b2){
	string manchester;
	manchester += b1;
	manchester += b2;
	string binary;
	if(manchester =="01"){
		binary += "1";
	}
	else if(manchester == "10"){
		binary += "0";
	}
	else {
		this->success = false;
		this->errorMessage = string(1, b1) + " and " + string(1, b2) + " are not valid manchester code.\n";
	}
	return binary;
}