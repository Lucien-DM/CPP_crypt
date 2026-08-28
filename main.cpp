#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "utils.hpp"

int main(int argc, char *argv[]){
        // first check existance of args
        if (argc < 4) {
                std::cout << "E: Too Few Arguments!\n";
                return 1;
        }
	std::string infile = argv[1]; //First argument is input file
        //Does infile Exist in the filesystem?
        if (utils::file_exists(infile) == false) {
                std::cout << '"' << infile << '"' << " Does not exist!\n";
        }
	std::string outfile = argv[2]; //Second arg is output file
        //TODO: Check mode
        //TODO: Get key
        //TODO: Read file into memory
        //TODO: Decrypt file
        //TODO: Write the file out again.

}
