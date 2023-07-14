#include "Compiler.hpp"

#include <Luau/Compiler.h>
#include <Luau/BytecodeBuilder.h>

static int encodeMult = 1;
class _ : public Luau::BytecodeEncoder {
public:
    std::uint8_t encodeOp(std::uint8_t op) override {
        return op * encodeMult;
    }
} encoder;

bool Compiler::compile() {
    encodeMult = 1;
    if (this->shouldEncode) {
        encodeMult = this->encodeMultiplier;
    }

    this->bytecode = Luau::compile(this->inputString, {}, {}, &encoder);

    if (this->bytecode.at(0) == '\0') { // syntax error
        return false;
    }

    return true;
}

const std::string& Compiler::getBytecode() {
    return this->bytecode;
}