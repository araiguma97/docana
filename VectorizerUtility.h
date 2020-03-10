#pragma once

#include <string>
#include <vector>

#include "DocumentElement.h"

class VectorizerUtility {
public:
    static void uniqueSort(std::vector<DocumentElement>* vec);
    static void toNouns(const std::vector<DocumentElement>& vec, std::vector<std::string>* nouns);
    static void toScores(const std::vector<DocumentElement>& vec, std::vector<double>* scores);
};
