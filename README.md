# docana

## 特徴

* 文書のベクトル化 (Bug of Words, tf-idf, Okapi BM25)
* 文書の特徴語抽出

## インストール

### 必要なもの
* C++ コンパイラ (g++ 7.4.0で動作を確認)
* [CMake](https://cmake.org/)
* [MeCab](https://taku910.github.io/mecab/)

### 手順
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

### 特徴語を抽出する

#### サンプルコード
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

#### 手順
1. 作成したプログラムをコンパイルする。
    ```sh
    g++ sample.cc -I/usr/local/include -L/usr/local/lib -ldocana -lmecab
    ```
1. docanaリポジトリ直下にあるdict.csv (辞書ファイル) を実行ファイルがあるディレクトリにコピーする。
1. 実行

#### 実行例
```
王 濁流 信実 暴君 友 王城 身代り 結婚式 磔 群衆
```

### 辞書を生成する

#### サンプルコード

```C++
// dict_gen.cc
#include <docana/dictionary_generator.h>

int main() {
    DictionaryGenerator dg;
    dg.generate();
}
```

#### 手順

1. コーパスとして用いるテキストファイルを入れたディレクトリ (以下、コーパスディレクトリと呼びます) を用意する。
1. `find`コマンドを用いて、「コーパスディレクトリ」から「コーパスパス一覧ファイル」を作成する。
    ```sh
    find <corpus_dir_name> -name "*.txt" > corpus_pathes.txt
    ```
1. 作成したプログラムをコンパイルする。
    ```sh
    g++ dict_gen.cc -I/usr/local/include -L/usr/local/lib -ldocana -lmecab
    ```
1. 「コーパスディレクトリ」と「コーパスパス一覧ファイル」を実行ファイルがあるディレクトリにコピーする。
1. 実行

#### 実行例
実行ファイルがあるディレクトリに辞書ファイル (dict.csv) が生成されます。
