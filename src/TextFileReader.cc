#include "TextFileReader.h"

#include <fstream>
#include <string>
#include <vector>

std::string TextFileReader::readAll(const std::string& file_path) {
    std::string text;

    std::ifstream file(file_path, std::ios::in);
    if (! file) {
        return text;
    }

    std::string line;
    while (std::getline(file, line)) {
        text += line;
    }
    
    return text;
}

void TextFileReader::readAll(const std::vector<std::string>& file_paths, std::vector<std::string>* file_texts) {
    for (std::string file_path : file_paths) {
        std::string file_text = readAll(file_path);
        if (! file_text.empty()) {
            file_texts->push_back(file_text);
        }
    }
}

bool TextFileReader::readLines(const std::string& file_path, std::vector<std::string>* lines) {
    std::string text;

    std::ifstream file(file_path, std::ios::in);
    if (! file) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        lines->push_back(line);
    }

    return true;
}

bool TextFileReader::readCsv(const std::string& file_path, std::vector<std::vector<std::string>>* values_list) {
    std::string text;

    std::ifstream file(file_path, std::ios::in);
    if (! file) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> values;
        split(line, ',', &values);
        values_list->push_back(values);
    }

    return true;
}

void TextFileReader::split(const std::string& str, const char delim, std::vector<std::string>* values) {
    std::string::size_type offset = 0;
    while (1) {
        std::string::size_type pos = str.find(delim, offset);
        if (pos == std::string::npos) {
           values->push_back(str.substr(offset)); 
           break;
        }
        values->push_back(str.substr(offset, pos - offset));
        offset = pos + 1;
    }
}

