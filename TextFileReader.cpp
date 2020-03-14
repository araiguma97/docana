#include "TextFileReader.h"

#include <fstream>
#include <string>
#include <vector>

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

void TextFileReader::read(const std::vector<std::string>& file_paths, std::vector<std::string>* file_texts) {
    for (std::string file_path : file_paths) {
        std::string file_text = read(file_path);
        file_texts->push_back(file_text);
    }
}
