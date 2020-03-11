#include "TextFileReader.h"


#include <iostream>
#include <fstream>
#include <string>

std::string TextFileReader::read(const std::string& file_path) {
    std::string text;

    std::ifstream file(file_path, std::ios::in);
    if (! file) {
        std::cerr << "error: File \"" << file_path << "\" not found." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    while (! file.eof()) {
        std::getline(file, line);    
        text += line;
    }
    
    return text;
}
