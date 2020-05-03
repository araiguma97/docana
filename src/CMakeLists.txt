cmake_minimum_required(VERSION 3.10)

include_directories(/usr/local/include ${PROJECT_SOURCE_DIR}/include)
link_directories(/usr/local/lib)
add_library(docana STATIC
    document_analyzer.cc

    vectorizer.cc
    bow_vectorizer.cc
    tfidf_vectorizer.cc
    bm25_vectorizer.cc
    document_element.cc

    cosine_similarity_calculator.cc
    documents_pair.cc

    noun_extractor.cc
    dictionary_generator.cc

    text_file_utility.cc
    vector_utility.cc
)
target_link_libraries(docana mecab)

INSTALL(
    TARGETS docana
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

INSTALL(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/docana
    DESTINATION include
)

