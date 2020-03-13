#include "TextFileReader.h"

#include <iostream>
#include <fstream>
#include <string>

std::string TextFileReader::read(const std::string& file_path) {
    std::string text;

    std::ifstream file(file_path, std::ios::in);
    if (! file) {
        return NULL;
    }

    std::string line;
    while (! file.eof()) {
        std::getline(file, line);    
        text += line;
    }
    
    return text;
}
