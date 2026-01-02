#include "docana/dictionary_generator.h"

#include <dirent.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "docana/document_element.h"
#include "docana/text_file_utility.h"
#include "docana/noun_extractor.h"
#include "docana/vector_utility.h"

class ProgressCounter {
public:
    ProgressCounter(int goal) {
        goal_ = goal;
    } 

    void count() {
        std::cout << cnt_ << "/" << goal_ << "\r";
        cnt_++;
    }
    
    void end() {
        std::cout << std::endl;
    }
private:
    int goal_;
    int cnt_ = 0;
};

bool DictionaryGenerator::generate() {
    // コーパスのパスを読み込む
    std::cout << "Reading corpus paths..." << std::endl;
    std::vector<std::string> corpus_paths = TextFileUtility::readLineByLine(corpus_paths_filename_);
    if (corpus_paths.empty()) {
        std::cerr << "[ERROR] Corpus paths file (=\"" << corpus_paths_filename_ << "\") is NULL." << std::endl;    
        return false;
    }
    
    // コーパスを読み込む
    std::cout << "Reading corpus..." << std::endl;
    std::vector<std::string> corpus_texts;
    ProgressCounter reading_pc(corpus_paths.size());
    for (std::string corpus_path : corpus_paths) {
        std::string corpus_text = TextFileUtility::read(corpus_path);
        if (corpus_text.empty()) {
            std::cerr << "[WARNING] Corpus file (=\"" << corpus_path << "\") is NULL." << std::endl;    
        } else {
            corpus_texts.push_back(corpus_text);
        }
        reading_pc.count();
    }
    reading_pc.end();

    // コーパスを辞書に変換
    std::cout << "Converting corpus to dictionary..." << std::endl;
    std::map<std::string, int> dict;
    int corpus_num = corpus_texts.size();
    int sum_dl = 0;
    ProgressCounter converting_pc(corpus_num);
    for (auto corpus_text : corpus_texts) { 
        NounExtractor ne;
        std::vector<std::string> raw_corpus_nouns = ne.extractNoun(corpus_text);
        std::vector<std::string> corpus_nouns = VectorUtility::unique(corpus_nouns);
        sum_dl += corpus_nouns.size();
        for (auto corpus_noun : corpus_nouns) {
            dict[corpus_noun]++;
        }
        converting_pc.count();
    }
    converting_pc.end();
    dict["$corpus_num"] = corpus_num;
    dict["$sum_dl"]     = sum_dl;

    // 辞書書き出し
    std::cout << "Write dictionary..." << std::endl;
    std::vector<std::vector<std::string>> dict_values_list;
    for (auto item : dict) {
        std::vector<std::string> dict_values;
        dict_values.push_back(item.first);
        dict_values.push_back(std::to_string(item.second));
        dict_values_list.push_back(dict_values);
    }
    TextFileUtility::writeCsv(dict_path_, dict_values_list);

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

    for (auto dict_values : dict_values_list) {
        (*dict)[dict_values[0]] = std::stoi(dict_values[1]);
    }

    return true;
}

