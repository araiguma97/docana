#include <string>
#include <vector>

class NounExtractor {
public:
    std::vector<std::string> extractNoun(const std::string& str);
private:
    std::vector<std::string> split(const std::string& str, const char delim);
};
