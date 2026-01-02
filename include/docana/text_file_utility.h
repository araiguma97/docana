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
     * @param file_path ファイルのパス
     * @retrun ファイルのテキスト
     */
    static std::string read(const std::string& file_path);

    /**
     * テキストファイルを行ごとに読み込む
     * @param file_path ファイルのパス
     * @return ファイルの行
     */
    static std::vector<std::string> readLineByLine(const std::string& file_pathr);
    
    /**
     * CSVファイルを読み込む
     * @param file_path ファイルのパス
     * @return ファイルの値一覧
     */
    static std::vector<std::vector<std::string>> readCsv(const std::string& file_path);

    /**
     * 文字列リストをCSVファイルに書き込む
     * @param 書き込む文字列リスト
     */
    static void writeCsv(const std::string& file_path, const std::vector<std::vector<std::string>>& values_list);

    /**
     * 文字列を任意の文字で分割する
     * @param str 文字列
     * @param delim 分割する任意の文字
     * @return 分割された値
     */
    static std::vector<std::string> split(const std::string& str, const char delim);
};

