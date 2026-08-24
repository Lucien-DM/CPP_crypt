#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
std::string infile = "";
std::string outfile = "";

inline bool file_exists (const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

int main(int argc, char *argv[]){
	// first check existance of args
	if (argc < 4) {
		std::cout << "Too Few Arguments!\n";
		return 1;
	}
	infile = argv[1];
	if (file_exists(infile) == false) {
		std::cout << '"' << infile << '"' << " Does not exist!\n";
	}
	outfile = argv[2];
	std::ifstream InputFile(infile);
}
