cmake_minimum_required(VERSION 3.10)

add_library(docana STATIC
    bm25_vectorizer.cc
    bow_vectorizer.cc
    cosine_similarity_calculator.cc
    dictionary_generator.cc
    document_analyzer.cc
    document_element.cc
    documents_pair.cc
    noun_extractor.cc
    text_file_utility.cc
    tfidf_vectorizer.cc
    vector_utility.cc
    vectorizer.cc
)

target_include_directories(docana PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_include_directories(docana PRIVATE
    ${MECAB_INCLUDE_DIR}
)
target_link_libraries(docana PRIVATE ${MECAB_LIBRARY})

INSTALL(
    TARGETS docana
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

INSTALL(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/docana
    DESTINATION include
)

