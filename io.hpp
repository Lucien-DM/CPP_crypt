#ifndef HEADERFILE_IO
#define HEADERFILE_IO

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <tuple>
#include <set>
#include "utils.hpp"

namespace io {

	bool validate_charset(std::string charset) {
	        /* This verifies that the charset is valid */
	        if (charset.length() != 62) {
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

	std::vector<std::string> read_file(std::string fname) {
	        /* Reads file and returns a vector of strings
	         * Does not validate if file exists */
	        std::vector<std::string> file_contents = {};
	        std::ifstream InputFile(fname); //Opens file - Remember to CLOSE
	        std::string line = ""; //declare and Init line var
	        while (getline (InputFile, line)) {
	                file_contents.push_back(line);
	        }
	        InputFile.close(); //Closes file
	        return file_contents;
	}

	std::tuple<std::string, int> input_key() {
        	/* Input the key from the user,
            	 * Validate it, and then return as an std::tuple
         	 * if not valid, repeat input until it is
         	 * store charset as std::string charset
         	 * store key itrator as int key_i */
        	std::string unvalidated_charset; //Charset for encryption
        	std::string str_unvalidated_key_i; //Key Itorater Value
        	int key_i;
        	while (true) {
        	        std::string key_cin;
        	        std::cout << "Key: " << std::flush;
        	        std::cin >> key_cin;
        	        {
        	                std::vector<std::string> temp = utils::split(key_cin, ':');
        	                unvalidated_charset = temp[0];
        	                str_unvalidated_key_i = temp[1];
        	        }
        	        if (validate_charset(unvalidated_charset)) {
        	                try {
        	                        key_i = std::stoi(str_unvalidated_key_i);
        	                        break;
        	                } catch (const std::out_of_range& e) {
        	                        std::cout << "Itorator too big!\nPlease use a smaller one.\n";
        	                }
        	        } else {
        	                std::cout << "Key is Invalid!\n";
        	        }
        	}
        	return std::make_tuple(unvalidated_charset, key_i);
	}

}

#endif
