#include "docana/bow_vectorizer.h"

#include <string>
#include <vector>

double BowVectorizer::calculate(const std::string& /*term*/, const size_t term_cnt, const size_t /*total_term_num*/) {
    return term_cnt;
}

