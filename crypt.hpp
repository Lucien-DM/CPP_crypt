/* GPL3 Licenced, Copyleft
 * This is a toy encryption system, based on a shifting replacement cypher.
 * This is not designed for legitimate Security applications and NO WARRENTY is supplied. */
/* Global TODOs here */
//TODO: Split this file into multiple source files
//TODO: Patch out the global comments
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "utils.hpp"
std::string charset; //Charset for replacement
int key_i; //Key Itorator
unsigned int iterate; //iteration value of the charset
const std::string BASE_CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"; //This must never change as it will break decryption from earlier versions	

unsigned int char_counter(const std::vector<std::string>& file, int key_i) {
	/* recreates the final itorator */
	unsigned int count = 0;
	for (const std::string& line : file) {
		for (char c : line) {
			unsigned int temp;
			temp = count + key_i;
			count = temp;
		}
	}
	return count;
}

char letter_replacer(char l, unsigned int iterator) {
	/* input the character, and iterator, and then replace the character with the appropriate encrypted char
	 * Input from args, output as return value
	 * If not in BASE_CHARSET constant, return char l */
	size_t index = BASE_CHARSET.find(l);
	if (index == std::string::npos) {
        	return l;  // not in charset, passthrough
	}
	unsigned int encrypted_index = (index + iterator) % 62 ;
	char encrypted_l = charset[encrypted_index];
	return encrypted_l;
}

char letter_dereplacer(char encrypted_l, unsigned int iterator) {
	/* Inverse operation to letter_replacer */
	size_t index = charset.find(encrypted_l);
	if (index == std::string::npos) {
		return encrypted_l;  // not in charset, passthrough
	}
	unsigned int original_index = (index - iterator % 62 + 62) % 62;
	char original_l = BASE_CHARSET[original_index];
	return original_l;
}

std::string line_encrypt(std::string& og_line) {
	/* Encrypts the whole line inputted as std::string
	 * Also ticks over the cypher shift */   
	std::string encrypted_line;
	for (char c : og_line) {
		encrypted_line += (letter_replacer(c, iterate));
		iterate += key_i;
	}
	return encrypted_line;
}

std::string line_decrypt(std::string& encrypted_line) {
	/* The inverse of line_encrypt */
	std::string og_line;
	for (char c : encrypted_line) {
		iterate -= key_i;
		og_line += (letter_replacer(c, iterate));
	}
	return og_line;
}

std::vector<std::string> file_encrypt(std::vector<std::string>& plain_file) {
	/* takes the file stored in memory as a std::vector<std::string>
	 * and wraps other functions to encrypt it
	 * WARN: clears the vector passed to it as a means of memory management */
	std::vector<std::string> encrypted_file;
	for (std::string& line : plain_file) {
		encrypted_file.push_back(line_encrypt(line));
		line.clear(); //Destructive! Clears line from vector to free memory
	}
	return encrypted_file;
}

std::vector<std::string> file_decrypt(std::vector<std::string>& encrypted_file) {
	/* Inverse of file_encrypt
	 * WARN: is destructive to input std::vector<std::string>& encrypted_file
	 * for sake of memory management */
	std::vector<std::string> plain_file;
	for (std::string& line : encrypted_file) {
		plain_file.push_back(line_decrypt(line));
		line.clear(); //Destructive! Clears line from the vector to free memory
	}
	return plain_file;
}
