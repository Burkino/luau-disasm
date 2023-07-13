#include <string>

class Compiler {
private:
    std::string inputString;
    std::string bytecode;
public:
    Compiler(const std::string& input) : inputString(input) {}
    bool compile();
    const std::string& getBytecode();
};