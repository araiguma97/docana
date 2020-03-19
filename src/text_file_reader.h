/**
 * @file text_file_reader.h
 */
#pragma once

#include <string>
#include <vector>

/**
 *  テキストファイルを読み込むクラス。
 */
class TextFileReader {
public:
    /**
     * テキストファイルの全テキストを読み込む
     * @param [in] file_path ファイルのパス
     * @retrun ファイルのテキスト
     */
    std::string readAll(const std::string& file_path);

    /**
     * テキストファイル群の全テキストを読み込む
     * @param [in] file_path ファイルのパス一覧
     * @param [out] ファイルのテキスト一覧
     */
    void readAll(const std::vector<std::string>& file_paths, std::vector<std::string>* file_texts);
    
    /**
     * テキストファイルを行ごとに読み込む
     * @param [in] file_path
     * @param [out] ファイルの行
     */
    bool readLines(const std::string& file_path, std::vector<std::string>* lines);
    
    /**
     * CSVファイルの値を読み込む
     * @param [in] file_path ファイルのパス
     * @param [out] ファイルの値一覧
     */
    bool readCsv(const std::string& file_pats, std::vector<std::vector<std::string>>* values_list);

    /**
     * 文字列を任意の文字で分割する
     * @param [in] str 文字列
     * @param [in] delim 分割する任意の文字
     * @param [out] 分割された値
     */
    void split(const std::string& str, const char delim, std::vector<std::string>* values);
};
