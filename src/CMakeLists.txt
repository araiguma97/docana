cmake_minimum_required(VERSION 3.10)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_library(docana STATIC
    noun_extractor.cc
    term_extractor.cc
    vectorizer.cc
    bow_vectorizer.cc
    tfidf_vectorizer.cc
    bm25_vectorizer.cc
    document_element.cc
    dictionary_generator.cc
    text_file_utility.cc
    vector_utility.cc
)
target_link_libraries(docana mecab)

