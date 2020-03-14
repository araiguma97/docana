/**
 * @file TextFileReader.h
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
     * テキストファイルを読み込む
     * @param file_path ファイルのパス
     * @retrun ファイルのテキスト
     */
    std::string read(const std::string& file_path);

    /**
     * テキストファイルを読み込む
     * @param file_path ファイルのパス一覧
     * @retrun ファイルのテキスト一覧
     */
    void read(const std::vector<std::string>& file_paths, std::vector<std::string>* file_texts);
};
