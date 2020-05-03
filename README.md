# docana

## 特徴

* 文書のベクトル化 (Bug of Words, tf-idf, Okapi BM25)
* 文書の特徴語抽出

## インストール

1. [MeCab](https://taku910.github.io/mecab/#install)をインストール
1. docanaをインストール
    ```sh
    git clone https://github.com/araiguma97/docana.git
    cd docana
    mkdir build
    cd build
    cmake ..
    make
    make install
    ```
1. ソースコードを作成
    ```C++
    // sample.cc
    #include <iostream>
    #include <docana/term_extractor.h>

    int main() {
        std::vector<std::string> terms;
        
        // "hashire_merosu.txt"から特徴語を10個抽出
        TermExtractor te; 
        te.extract("hashire_merosu.txt", 10, &terms);
        
        // 特徴語を表示
        for (auto term : terms) {
            std::cout << term << " ";
        }
        std::cout << std::endl;
    }
    ```
1. コンパイル
    ```sh
    g++ sample.cc -I/usr/local/include -L/usr/local/lib -ldocana -lmecab
    ```
1. docanaリポジトリ直下にあるdict.csv (辞書ファイル) を実行ファイルがあるディレクトリにコピー
1. 実行
    ```
    ./a.out
    王 濁流 信実 暴君 友 王城 身代り 結婚式 磔 群衆
    ```


## 辞書の生成
1. コーパスとして用いるテキストファイル (文字コードはUTF-8、改行コードはLF) を入れたディレクトリ (以下、「コーパスディレクトリ」と呼ぶ) を用意する。
1. `find`コマンドを用いて、「コーパスパス一覧ファイル」を作成する。
    ```sh
    find <corpus_dir_name> -name "*.txt" > corpus_pathes.txt
    ```
1. ソースコードを作成
    ```C++
    // dict_gen.cc
    #include <docana/dictionary_generator.h>

    int main() {
        DictionaryGenerator dg;
        dg.generate();
    }
    ```
1. コンパイル
    ```sh
    g++ dict_gen.cc -I/usr/local/include -L/usr/local/lib -ldocana -lmecab
    ```
1. 「コーパスディレクトリ」と「コーパスパス一覧ファイル」を実行ファイルがあるディレクトリにコピーする。
1. 実行すると、辞書ファイル (dict.csv) を生成する。
