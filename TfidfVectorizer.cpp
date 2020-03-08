#include "TfidfVectorizer.h"

TfidfVectorizer::TfidfVectorizer(const std::vector<std::string>& corpus_texts) {
    NounExtractor ne;
    ne.extractNoun(corpus_texts, &corpus_nouns_list_);
}

void TfidfVectorizer::vectorize(const std::string& doc_text, const std::vector<std::string
>& key_nouns, std::vector<DocumentElement>* doc_vec) {
    for (std::string key_noun : key_nouns) {
        DocumentElement doc_ele = {key_noun, calculate(key_noun, doc_text)};
        doc_vec->push_back(doc_ele);
    }
}

double TfidfVectorizer::calculate(const std::string& noun, const std::string& doc_text) {
    NounExtractor ne;
    std::vector<std::string> doc_nouns;
    ne.extractNoun(doc_text, &doc_nouns);

    int noun_cnt = 0;
    for (std::string doc_noun : doc_nouns) {
        if (noun == doc_noun) {
            noun_cnt++;
        }
    }
    double tf = (double)noun_cnt / doc_nouns.size();

    int doc_cnt = 0;
    for (std::vector<std::string> corpus_nouns : corpus_nouns_list_) {
        for (std::string corpus_noun : corpus_nouns) {
            if (noun == corpus_noun) {
                doc_cnt++;
                break;
            }
        }
    }
    double idf = std::log((double)corpus_nouns_list_.size() / (doc_cnt + 1));

    return tf * idf;
}
