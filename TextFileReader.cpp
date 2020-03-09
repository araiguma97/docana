#include "TextFileReader.h"

#include <fstream>
#include <string>

std::string TextFileReader::readTextFile(const std::string& file_path) {
    std::string text;

    std::ifstream file(file_path, std::ios::in);
    std::string line;
    while (! file.eof()) {
        std::getline(file, line);    
        text += line;
    }
    
    return text;
}
