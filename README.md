# docana
## 特徴
* 文書のベクトル化 (Bug of Words, tf-idf, Okapi BM25)
* 文書の特徴語抽出
* 文書の類似度計算 (コサイン類似度)

## 使い方
1. [MeCab](https://taku910.github.io/mecab/)をインストールする。
2. `git clone https://github.com/araiguma97/docana.git` する。
3. 日本語の文書が入力されたtxtファイルを複数個用意する。コーパスとして用います。

### サンプルコード
```C++
#include <string>
#include <vector>

#include "VectorizerFactory.h"
#include "DocumentAnalyzer.h"

// コーパスとして用いるtxtファイルを指定
std::vector<std::string> corpus_file_paths = {
  "1.txt", "2.txt", "3.txt", "4.txt",
  "5.txt", "6.txt", "7.txt", "8.txt",
};

/* (1) 文書解析器の生成 */
VectorizerFactory vf;
DocumentAnalyzer da(corpus_file_paths, vf.create(TFIDF));      // tf-idf でベクトル化
// DocumentAnalyzer da(corpus_file_paths, vf.create(BOW));     // Bug of Words でベクトル化
// DocumentAnalyzer da(corpus_file_paths, vf.create(BM25));    // Okapi BM25でベクトル化

/* (2) 文書から特徴語を抽出 */
std::vector<std::string> terms;
da.extractTerm("wagahaiwa_nekodearu.txt", 10, &terms);    // "wagahaiwa_nekodearu.txt"から特徴語を10個抽出

/* (3) 特徴語を表示 */
std::cout << "Terms=[";
for (std::string term : terms) {
  std::cout << term << ", ";
}
std::cout << "]" <<std::endl;
```
### 出力例
```
Terms=[主人, 猫, 書生, 教師, 絵, 車屋, 例, 書斎, 黒, 供, 砂糖, ]
```
