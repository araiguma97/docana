#include "dictionary_editor.h"

#include <dirent.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "document_element.h"
#include "text_file_reader.h"
#include "text_file_writer.h"
#include "noun_extractor.h"
#include "vector_utility.h"

void DictionaryEditor::createDictionary(const std::string& find_file_path) {
    // コーパスのパス読み込み
    TextFileReader tfr;
    std::vector<std::string> corpus_paths;
    tfr.readLines(find_file_path, &corpus_paths);
    
    // コーパステキスト読み込み
    std::cout << "Loading Corpus.... " << std::endl;
    std::vector<std::string> corpus_texts;
    for (std::string corpus_path : corpus_paths) {
        std::string corpus_text = tfr.readAll(corpus_path);
        if (! corpus_text.empty()) {
            corpus_texts.push_back(corpus_text);
        }
    }
    
    // コーパスを辞書に変換
    std::map<std::string, int> dict;
    int corpus_num = corpus_texts.size();
    int sum_dl = 0;
    int progress = 0;
    for (auto corpus_text : corpus_texts) { 
        NounExtractor ne;
        std::vector<std::string> corpus_nouns;
        ne.extractNoun(corpus_text, &corpus_nouns);
        VectorizerUtility::unique(&corpus_nouns);
        sum_dl += corpus_nouns.size();
        for (auto corpus_noun : corpus_nouns) {
            dict[corpus_noun]++;
        }
        std::cout << progress << "/" << corpus_num << " Loaded\r";
        progress++;
    }
    std::cout << std::endl;
    dict["$corpus_num"] = corpus_num;
    dict["$sum_dl"]     = sum_dl;

    // コーパス書き出し
    std::vector<std::vector<std::string>> dict_values_list;
    for (auto item : dict) {
        std::vector<std::string> dict_values;
        dict_values.push_back(item.first);
        dict_values.push_back(std::to_string(item.second));
        dict_values_list.push_back(dict_values);
    }
    TextFileWriter tfw;
    tfw.writeCsv(dict_values_list);
}

bool DictionaryEditor::readDictionary(std::map<std::string, int>* dict) {
    if (dict == nullptr) {
        return false;
    }

    TextFileReader tfr;
    std::vector<std::vector<std::string>> dict_values_list;
    tfr.readCsv("../dict", &dict_values_list);

    for (auto dict_values : dict_values_list) {
        (*dict)[dict_values[0]] = std::stoi(dict_values[1]);
    }
}

