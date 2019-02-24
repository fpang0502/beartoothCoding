#ifndef MANCHESTER_H
#define MANCHESTER_H
#include <string>
#include <fstream>

class Manchester {
public:
	// Constructor
	Manchester();
	// Destructor
	~Manchester();
	// parse function to call encode and decode
	bool parse(std::string mode, std::string inputfile, std::string outputfile);
	// get errorMessage
	void getMessage();
private:
	// encode
	void encode(std::ifstream& ifile, std::ofstream& ofile);
	// decode
	void decode(std::ifstream& ifile, std::ofstream& ofile);
	// convert 8 bit binary to manchester
	std::string binaryToManchester(std::string s);
	// convert 2 bit manchester to binary
	std::string manchesterToBinary(char b1, char b2);
	// error message
	std::string errorMessage;
	// if parse was success
	bool success;
};

#endif