/**
 * @file text_file_reader.h
 */
#pragma once

#include <string>
#include <vector>

/**
 *  テキストファイル入出力の便利クラス。
 */
class TextFileUtility {
public:
    /**
     * テキストファイルを読み込む
     * @param [in] file_path ファイルのパス
     * @retrun ファイルのテキスト
     */
    static std::string read(const std::string& file_path);

    /**
     * テキストファイルを行ごとに読み込む
     * @param [in] file_path
     * @param [out] ファイルの行
     */
    static bool readLineByLine(const std::string& file_path, std::vector<std::string>* lines);
    
    /**
     * CSVファイルを読み込む
     * @param [in] file_path ファイルのパス
     * @param [out] ファイルの値一覧
     */
    static bool readCsv(const std::string& file_pats, std::vector<std::vector<std::string>>* values_list);

    /**
     * 文字列リストをCSVファイルに書き込む
     * @param [in] 書き込む文字列リスト 
     */
    static void writeCsv(const std::vector<std::vector<std::string>>& values_list);

    /**
     * 文字列を任意の文字で分割する
     * @param [in] str 文字列
     * @param [in] delim 分割する任意の文字
     * @param [out] 分割された値
     */
    static void split(const std::string& str, const char delim, std::vector<std::string>* values);
};

