#include "Compiler.hpp"

#include <Luau/Compiler.h>

bool Compiler::compile() {
    this->bytecode = Luau::compile(this->inputString);

    if (this->bytecode.at(0) == '\0') { // syntax error
        return false;
    }

    return true;
}

const std::string& Compiler::getBytecode() {
    return this->bytecode;
}