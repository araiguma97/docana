#include "docana/dictionary_generator.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "docana/text_file_utility.h"
#include "docana/noun_extractor.h"
#include "docana/vector_utility.h"


bool DictionaryGenerator::generate() {
    // コーパスのパスを読み込む
    std::cout << "Reading corpus paths..." << std::endl;
    std::vector<std::string> corpus_paths = TextFileUtility::readLineByLine(corpus_paths_filename_);
    if (corpus_paths.empty()) {
        std::cerr << "[ERROR] Corpus paths file (=\"" << corpus_paths_filename_ << "\") is NULL." << std::endl;    
        return false;
    }
    
    // コーパスを1ファイルずつ読み込み・変換
    std::cout << "Converting corpus to dictionary..." << std::endl;
    std::map<std::string, int> dict;
    int corpus_num = 0;
    long long sum_dl = 0;
    NounExtractor ne;
    for (const auto& corpus_path : corpus_paths) {
        std::string corpus_text = TextFileUtility::read(corpus_path);
        if (corpus_text.empty()) {
            std::cerr << "[WARNING] Corpus file (=\"" << corpus_path << "\") is NULL." << std::endl;
            continue;
        }
        std::vector<std::string> raw_corpus_nouns = ne.extractNoun(corpus_text);
        sum_dl += raw_corpus_nouns.size();
        std::vector<std::string> corpus_nouns = VectorUtility::unique(raw_corpus_nouns);
        for (const auto& corpus_noun : corpus_nouns) {
            dict[corpus_noun]++;
        }
        corpus_num++;
    }
    dict["$corpus_num"] = corpus_num;
    dict["$sum_dl"]     = static_cast<int>(sum_dl);

    // 辞書書き出し
    std::cout << "Write dictionary..." << std::endl;
    std::ofstream ofs(dict_path_);
    if (!ofs) {
        std::cerr << "[ERROR] Cannot open dictionary file for writing." << std::endl;
        return false;
    }
    for (const auto& item : dict) {
        ofs << item.first << "," << item.second << "\n";
    }

    return true;
}

bool DictionaryGenerator::read(std::map<std::string, int>* dict) {
    if (dict == nullptr) {
        std::cerr << "[ERROR] Dictionary map is NULL." << std::endl;    
        return false;
    }

    std::vector<std::vector<std::string>> dict_values_list = TextFileUtility::readCsv(dict_path_);
    if (dict_values_list.empty()) {
        std::cerr << "[ERROR] Dictionary file not found." << std::endl;    
        return false;
    }

    for (const auto& dict_values : dict_values_list) {
        if (dict_values.size() < 2) {
            continue;
        }
        try {
            (*dict)[dict_values[0]] = std::stoi(dict_values[1]);
        } catch (const std::invalid_argument&) {
            std::cerr << "[WARNING] Invalid value in dictionary: " << dict_values[1] << std::endl;
            continue;
        }
    }

    return true;
}

