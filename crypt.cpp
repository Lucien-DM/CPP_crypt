#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <set>
#include <sstream>
std::string infile = ""; //Input File
std::string outfile = ""; //Output File
std::string charset; //Charset for replacement
std::string key_i; //Key Itorator
const std::string BASE_CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
inline bool file_exists (const std::string& name) {
	//This function was taken from stack overflow
	//checks existence of a file in the FS
	std::ifstream f(name.c_str());
	return f.good();
}

inline std::vector<std::string> split (const std::string split_string, char seporator) {
	//Code taken from stack overflow
	//Splits a string into a vector of strings by a seporator char
	std::string segment;
	std::vector<std::string> seglist;
	std::stringstream ss(split_string);
	while(std::getline(ss, segment, seporator))
	{
	   seglist.push_back(segment);
	}
	return seglist;
}

bool validate_charset(std::string charset) {
	// This verifies that the charset is valid
	if (charset.length() != 62) {
		return false;
	}
	if (charset == BASE_CHARSET) {
		return false;
	}
	std::set<char> seen = {};
	for (char c : charset) {
		if (seen.find(c) != seen.end()) {
			return false;
		} else {
			seen.insert(c);
		}
	}
	return true;
}

void input_key() {
	/* Input the key from the user,
	 * Validate it, and then store as a global var
	 * if not valid, repeat input until it is
	 * store charset as std::string charset
	 * store key itrator as int key_i */
	while (true) {
		std::string key_cin;
		std::cout << "Key: " << std::flush;
		std::cin >> key_cin;
		std::string unvalidated_charset; //Charset for encryption
		std::string str_unvalidated_key_i; //Key Itorater Value
		{
			std::vector<std::string> temp = split(key_cin, ':');
			unvalidated_charset = temp[0];
			str_unvalidated_key_i = temp[1];
		}
		if (validate_charset(unvalidated_charset)) {
			try {
				int check = std::stoi(str_unvalidated_key_i);
				charset = unvalidated_charset;
				key_i = check;
				break;
			} catch (const std::out_of_range& e) {
				std::cout << "Itorator too big!\nPlease use a smaller one.\n";
			}
		} else {
			std::cout << "Key is Invalid!\n";
		}		
	}
	return;
}	

char letter_replacer(char l, unsigned int iterator) {
	size_t index = BASE_CHARSET.find(l);
	if (index == std::string::npos) {
        	return l;  // not in charset, passthrough
	}
	unsigned int encrypted_index = (index + iterator) % 62 ;
	char encrypted_l = charset[encrypted_index];
	return encrypted_l;
}

char letter_dereplacer(char encrypted_l, unsigned int iterator) {
    size_t index = charset.find(encrypted_l);
    if (index == std::string::npos) {
        return encrypted_l;  // not in charset, passthrough
    }
    unsigned int original_index = (index - iterator % 62 + 62) % 62;
    char original_l = BASE_CHARSET[original_index];
    return original_l;
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
