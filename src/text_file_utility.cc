#include "text_file_utility.h"

#include <fstream>
#include <string>
#include <vector>

std::string TextFileUtility::read(const std::string& file_path) {
    std::string text;

    std::ifstream file(file_path, std::ios::in);
    if (! file) {
        return text;  // 空文字
    }

    std::string line;
    while (std::getline(file, line)) {
        text += line;
    }
    
    return text;
}

bool TextFileUtility::readLineByLine(const std::string& file_path, std::vector<std::string>* lines) {
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

bool TextFileUtility::readCsv(const std::string& file_path,
                              std::vector<std::vector<std::string>>* values_list) {
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

void TextFileUtility::writeCsv(const std::string& file_path,
                               const std::vector<std::vector<std::string>>& values_list) {
    std::string text;

    std::ofstream file(file_path);

    for (auto values : values_list) {
        for (auto value : values) {
            file << value << ",";
        }
        file << std::endl;
    }

    file.close();
}

void TextFileUtility::split(const std::string& str, const char delim, std::vector<std::string>* values) {
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

