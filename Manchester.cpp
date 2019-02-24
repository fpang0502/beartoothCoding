#include <iostream>
#include <sstream>
#include <bitset>
#include "Manchester.h"

using namespace std;

Manchester::Manchester(){
	this->errorMessage = "There is nothing wrong!\n";
	this->success=true;
}

Manchester::~Manchester()
{

}

void Manchester::getMessage(){
	cout << this->errorMessage << endl;
}

bool Manchester::parse(std::string mode, std::string inputfile, std::string outputfile){
	// take in 3 arguments -d/-e inputfile outputfile
	ifstream ifile;
	ifile.open(inputfile);
	ofstream ofile;
	ofile.open(outputfile);
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
		else {
			this->success = false;
			this->errorMessage = "Invalid parameter. Expected -e for encoding or -d for decoding.\n";
		}
	}
	this->getMessage();
	return false;
}


void Manchester::encode(ifstream& ifile, ofstream& ofile){
	string line;
	while(getline(ifile, line)){
		stringstream ss(line +"\n");
		char c;
		ss >> noskipws;
		while(ss>>c){
			string binary = bitset<8>(c).to_string();
			string manchester = binaryToManchester(binary);
			if(!this->success){
				ifile.close();
				ofile.close();
				return;
			}
			ofile << manchester;
		}
	}
	ifile.close();
	ofile.close();
	this->success = true;
	this->errorMessage = "Finished encoding!\n"; 
}

void Manchester::decode(ifstream& ifile, ofstream& ofile){
	string line;
	while(getline(ifile, line)){
		stringstream ss(line);
		for(unsigned int i=0; i<line.size(); i+=16){
			string binary;
			for(unsigned int j=i; j<i+16; j+=2){
				binary += this->manchesterToBinary(line[j], line[j+1]);
				if(!this->success){
					ifile.close();
					ofile.close();
					return;
				}
			}
			char letter = bitset<8>(binary).to_ulong();
			ofile << letter;
		}
	}
	ifile.close();
	ofile.close();
	this->success = true;
	this->errorMessage = "Finished decoding!\n"; 
}

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