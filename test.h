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
    static bool assertStrEq(std::string expected, std::string actual); 
    static bool assertSizeTypeEq(std::string::size_type expected, std::string::size_type actual);
    static bool assertStrVecEq(std::vector<std::string> expecteds, std::vector<std::string> actuals);
    static bool assertDocVecEq(DocumentVector expected, DocumentVector actuals);
};
