#include <string>
#include <vector>

class Test{
public:
    static bool debugNounExtractor(); 
private:
    static bool assertStrEq(std::string expected, std::string actual); 
    static bool assertSizeTypeEq(std::string::size_type expected, std::string::size_type actual);
    static bool assertStrVecEq(std::vector<std::string> expecteds, std::vector<std::string> actuals);
};
