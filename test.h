#include "DocumentVector.h"

#include <string>
#include <vector>

class Test{
public:
    static bool debugAll();
    static bool debugNounExtractor(); 
    static bool debugBowVectorizer();
private:
    static bool assertDoubleEq(double expected, double actual); 
    static bool assertStrEq(const std::string& expected, const std::string& actual); 
    static bool assertSizeTypeEq(std::string::size_type expected, std::string::size_type actual);
    static bool assertStrVecEq(const std::vector<std::string>& expecteds, const std::vector<std::string>& actuals);
    static bool assertDocVecEq(const DocumentVector& expecteds, const DocumentVector& actuals);
};
