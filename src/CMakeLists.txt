cmake_minimum_required(VERSION 3.10)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_library(docana STATIC
    main.cc
    noun_extractor.cc
    document_element.cc
    bow_vectorizer.cc
    tfidf_vectorizer.cc
    text_file_reader.cc
    vector_utility.cc
    document_analyzer.cc
    cosine_similarity_calculator.cc
    vectorizer.cc
    bm25_vectorizer.cc
    text_file_writer.cc
    documents_pair.cc
    dictionary_generator.cc
)

target_link_libraries(docana mecab)
