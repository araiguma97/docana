/**
 * @file TextFileWriter.h
 */
#pragma once

#include <string>
#include <vector>

class TextFileWriter {
public:
    /**
     * 値リストをCSVファイルに書き込む
     * @param [in] 書き込む値リスト 
     */
    void writeCsv(const std::vector<std::vector<std::string>>& values_list);
};

