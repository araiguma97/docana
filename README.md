# docana

## Features

* Documents vectorization (Bug of Words, tf-idf, Okapi BM25)
* Term Extraction from documents
* Calculation document similarity (Cosine similarity)
* Finding similar documents

## Requirement

* g++
* CMake
* [MeCab](https://taku910.github.io/mecab/)

## Installation

```sh
git clone https://github.com/araiguma97/docana.git
cd docana/docana
mkdir build
cd build
cmake ..
make
make install
```

## Usage

### Term Extraction from documents

1. Compile the following code.

    ```C++
    // sample.cc
    #include <iostream>
    #include <docana/term_extractor.h>

    int main() {
        std::vector<std::string> terms;

        // Extraction 10 terms from "hashire_merosu.txt"
        TermExtractor te;
        te.extract("hashire_merosu.txt", 10, &terms);

        // Show terms
        for (auto term : terms) {
            std::cout << term << " ";
        }
        std::cout << std::endl;
    }
    ```

    ```sh
    g++ sample.cc -I/usr/local/include -L/usr/local/lib -ldocana -lmecab
    ```

1. Copy the dictionary file (docana/dict.csv) to the directory containing an executable file.
1. Run, and terms are extracted.

    ```sh
    王 濁流 信実 暴君 友 王城 身代り 結婚式 磔 群衆
    ```

### Dictionary generation

1. Prepare text files to be used as corpus, and put them in a directory.
1. Make a corpus list file.

    ```sh
    find <corpus_dir_name> -name "*.txt" > corpus_list.txt
    ```

1. Compile the following code.

    ```cpp
    // dict_generationcc
    #include <docana/dictionary_generator.h>

    int main() {
        DictionaryGenerator dg;
        dg.generate();
    }
    ```

    ```sh
    g++ dict_generation.cc -I/usr/local/include -L/usr/local/lib -ldocana -lmecab
    ```

1. Copy the corpus directory and the corpus list file to the directory containing an executable file.

1. Run, and then a dictionary file (dict.csv) is generated.
