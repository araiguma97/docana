# docana

## 特徴

* 文書のベクトル化（Bug of Words, tf-idf, Okapi BM25）
* 文書の特徴後抽出
* 文書間の類似度計算（コサイン類似度）
* 類似文書検索

## 必要なもの

* g++
* CMake
* [MeCab](https://taku910.github.io/mecab/)

## インストール

```sh
git clone https://github.com/araiguma97/docana.git
cd docana/docana
mkdir build
cd build
cmake ..
make
make install
```

## 使い方

### 文書の特徴後抽出

1. 次のコードをコンパイルする

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

1. 辞書ファイル（docana/dict.csv）を実行ファイルがあるディレクトリにコピーする
1. 実行すると、文書の特徴語が表示される

    ```sh
    王 濁流 信実 暴君 友 王城 身代り 結婚式 磔 群衆
    ```

### 辞書生成

1. コーパスとして用いるテキストファイルをひとつのディレクトリに入れておく
1. 次のコマンドで、コーパスリストファイルを作成する

    ```sh
    find <corpus_dir_name> -name "*.txt" > corpus_list.txt
    ```

1. 次のコードをコンパイルする

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

1. コーパスを入れておいたディレクトリとコーパスリストファイルを実行ファイルがあるディレクトリにコピーする

1. 実行すると、辞書ファイル（dict.csv）が生成される
