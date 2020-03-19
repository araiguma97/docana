#include "text_file_writer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void TextFileWriter::writeCsv(const std::vector<std::vector<std::string>>& values_list) {
    std::string text;

    std::ofstream file("dict");

    for (auto values : values_list) {
        for (auto value : values) {
            file << value << ",";
        }
        file << std::endl;
    }

    file.close();
}
