#ifndef MANCHESTER_H
#define MANCHESTER_H
#include <string>
#include <fstream>

class Manchester {
public:
	Manchester();
	~Manchester();
	bool parse(std::string mode, std::string inputfile, std::string outputfile);
	void getMessage();
private:
	void encode(std::ifstream& ifile, std::ofstream& ofile);
	void decode(std::ifstream& ifile, std::ofstream& ofile);
	std::string binaryToManchester(std::string s);
	std::string manchesterToBinary(char b1, char b2);
	std::string errorMessage;
	bool success;
};

#endif