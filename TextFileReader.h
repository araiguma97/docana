/**
 * @file TextFileReader.h
 */

#pragma once

#include <string>

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
};
