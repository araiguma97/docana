# docana
## 特徴
* 文書のベクトル化 (Bug of Words, tf-idf, Okapi BM25)
* 文書の特徴語抽出
* -文書の類似度計算 (コサイン類似度)-

## 使い方
1. [MeCab](https://taku910.github.io/mecab/)をインストールする。
2. `git clone https://github.com/araiguma97/docana.git` する。

### サンプルコード
```C++
#include <iostream>
#include "docana/DocumentAnalyzer.h"

// "hashire_merosu.txt"から特徴語を10個抽出
int main() {
  std::vector<std::string> terms;

  DocumentAnalyzer da(); 
  da.extractTerm("hashire_merosu.txt", 10, &terms);
  
  for (std::string term : terms) {
    std::cout << term << " ";
  }
}
```
### 出力例
```
王 濁流 信実 暴君 友 王城 身代り 結婚式 磔 群衆
```
