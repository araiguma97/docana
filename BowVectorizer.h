#include "DocumentVector.h"

#include <string>
#include <vector>

class BowVectorizer {
public:
    ~BowVectorizer();
    DocumentVector* vectorize(const std::string& docText);
private:
    DocumentVector* docVec;
    int calculate(const std::string& targetNoun, const std::vector<std::string>& docNouns);
};
