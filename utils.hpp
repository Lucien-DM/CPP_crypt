#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
namespace utils {
	inline bool file_exists (const std::string& name) {
	        /* This function was taken from stack overflow
	         * checks existence of a file in the FS */
	        std::ifstream f(name.c_str());
	        return f.good();
	}
	
	inline std::vector<std::string> split (const std::string& split_string, char separator) {
	        /* Code taken from stack overflow
	         * Splits a string into a vector of strings by a seperator char */
	        std::string segment;
	        std::vector<std::string> seglist;
	        std::stringstream ss(split_string);
	        while(std::getline(ss, segment, separator))
	        {
	           seglist.push_back(segment);
	        }
	        return seglist;
	}
}

#endif
