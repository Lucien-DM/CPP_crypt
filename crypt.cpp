#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
std::string infile = "";
std::string outfile = "";

inline bool file_exists (const std::string& name) {
	//This function was taken from stack overflow
	//checks existence of a file in the FS
	std::ifstream f(name.c_str());
	return f.good();
}

std::vector<std::string> read_file(std::string fname) {
	/* Reads file and returns a vector of strings
	 * Does not validate if file exists */
	std::vector<std::string> file_contents = {};
	std::ifstream InputFile(fname); //Opens file - Remember to CLOSE
	std::string line = "";
	while (getline (InputFile, line)) {
		file_contents.push_back(line);
	}
	InputFile.close(); //Closes file
	return file_contents;
}

int main(int argc, char *argv[]){
	// first check existance of args
	if (argc < 4) {
		std::cout << "E: Too Few Arguments!\n";
		return 1;
	}
	infile = argv[1]; //First argument is input file
	//Does infile Exist in the filesystem?
	if (file_exists(infile) == false) {
		std::cout << '"' << infile << '"' << " Does not exist!\n";
	}
	outfile = argv[2]; //Second arg is output file
}
