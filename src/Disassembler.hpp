#include <string>
#include <sstream>

#include <Luau/lobject.h>

class Disassembler {
private:
    std::string inputBytecode;
    std::stringstream stream;

    void write(const char* format, ...);
    void processProto(Proto* p, Proto* parent);
public:
    Disassembler(const std::string& input) : inputBytecode(input) {}
    bool disassemble();
    std::string getStreamData();
};