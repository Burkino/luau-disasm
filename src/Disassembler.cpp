#include "Disassembler.hpp"

#include <map>

#include <Luau/lualib.h>
#include <Luau/lstate.h>
#include <Luau/lgc.h>
#include <Luau/lstring.h>
#include <Luau/lobject.h>
#include <Luau/lbytecode.h>

const std::map<std::uint8_t, std::string> opcodeMap = {
    {LOP_NOP, "NOP"},
    {LOP_BREAK, "BREAK"},
    {LOP_LOADNIL, "LOADNIL"},
    {LOP_LOADB, "LOADB"},
    {LOP_LOADN, "LOADN"},
    {LOP_LOADK, "LOADK"},
    {LOP_MOVE, "MOVE"},
    {LOP_GETGLOBAL, "GETGLOBAL"},
    {LOP_SETGLOBAL, "SETGLOBAL"},
    {LOP_GETUPVAL, "GETUPVAL"},
    {LOP_SETUPVAL, "SETUPVAL"},
    {LOP_CLOSEUPVALS, "CLOSEUPVALS"},
    {LOP_GETIMPORT, "GETIMPORT"},
    {LOP_GETTABLE, "GETTABLE"},
    {LOP_SETTABLE, "SETTABLE"},
    {LOP_GETTABLEKS, "GETTABLEKS"},
    {LOP_SETTABLEKS, "SETTABLEKS"},
    {LOP_GETTABLEN, "GETTABLEN"},
    {LOP_SETTABLEN, "SETTABLEN"},
    {LOP_NEWCLOSURE, "NEWCLOSURE"},
    {LOP_NAMECALL, "NAMECALL"},
    {LOP_CALL, "CALL"},
    {LOP_RETURN, "RETURN"},
    {LOP_JUMP, "JUMP"},
    {LOP_JUMPBACK, "JUMPBACK"},
    {LOP_JUMPIF, "JUMPIF"},
    {LOP_JUMPIFNOT, "JUMPIFNOT"},
    {LOP_JUMPIFEQ, "JUMPIFEQ"},
    {LOP_JUMPIFLE, "JUMPIFLE"},
    {LOP_JUMPIFLT, "JUMPIFLT"},
    {LOP_JUMPIFNOTEQ, "JUMPIFNOTEQ"},
    {LOP_JUMPIFNOTLE, "JUMPIFNOTLE"},
    {LOP_JUMPIFNOTLT, "JUMPIFNOTLT"},
    {LOP_ADD, "ADD"},
    {LOP_SUB, "SUB"},
    {LOP_MUL, "MUL"},
    {LOP_DIV, "DIV"},
    {LOP_MOD, "MOD"},
    {LOP_POW, "POW"},
    {LOP_ADDK, "ADDK"},
    {LOP_SUBK, "SUBK"},
    {LOP_MULK, "MULK"},
    {LOP_DIVK, "DIVK"},
    {LOP_MODK, "MODK"},
    {LOP_POWK, "POWK"},
    {LOP_AND, "AND"},
    {LOP_OR, "OR"},
    {LOP_ANDK, "ANDK"},
    {LOP_ORK, "ORK"},
    {LOP_CONCAT, "CONCAT"},
    {LOP_NOT, "NOT"},
    {LOP_MINUS, "MINUS"},
    {LOP_LENGTH, "LENGTH"},
    {LOP_NEWTABLE, "NEWTABLE"},
    {LOP_DUPTABLE, "DUPTABLE"},
    {LOP_SETLIST, "SETLIST"},
    {LOP_FORNPREP, "FORNPREP"},
    {LOP_FORNLOOP, "FORNLOOP"},
    {LOP_FORGLOOP, "FORGLOOP"},
    {LOP_FORGPREP_INEXT, "FORGPREP_INEXT"},
    {LOP_FORGPREP_NEXT, "FORGPREP_NEXT"},
    {LOP_NATIVECALL, "NATIVECALL"},
    {LOP_GETVARARGS, "GETVARARGS"},
    {LOP_DUPCLOSURE, "DUPCLOSURE"},
    {LOP_PREPVARARGS, "PREPVARARGS"},
    {LOP_LOADKX, "LOADKX"},
    {LOP_JUMPX, "JUMPX"},
    {LOP_FASTCALL, "FASTCALL"},
    {LOP_COVERAGE, "COVERAGE"},
    {LOP_CAPTURE, "CAPTURE"},
    {LOP_FASTCALL1, "FASTCALL1"},
    {LOP_FASTCALL2, "FASTCALL2"},
    {LOP_FASTCALL2K, "FASTCALL2K"},
    {LOP_FORGPREP, "FORGPREP"},
    {LOP_JUMPXEQKNIL, "JUMPXEQKNIL"},
    {LOP_JUMPXEQKB, "JUMPXEQKB"},
    {LOP_JUMPXEQKN, "JUMPXEQKN"},
    {LOP_JUMPXEQKS, "JUMPXEQKS"}
};

void Disassembler::write(const char* format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    this->stream << buffer;
}

void Disassembler::processProto(Proto* p, Proto* parent) {
    if (parent == nullptr) { // will only be the case for the main function
        lua_State* L = luaL_newstate();
        p->debugname = luaS_newlstr(L, "main", 4);
        lua_close(L);
    }

    if (p->is_vararg) {
        this->write("function %s(...)\n", p->debugname->data);
    } else {
        this->write("function %s(", p->debugname->data);
        for (int i = 1; i <= p->numparams; i++) {
            if (i == p->numparams) {
                this->write("arg%d", i);
            } else {
                this->write("arg%d, ", i);
            }
        }
        this->write(")\n");
    }

    for (int i = 0; i < p->sizecode; i++) {
        std::uint32_t insn = p->code[i];

        std::uint8_t opcode = LUAU_INSN_OP(insn);

        this->write("%s", opcodeMap.find(opcode)->second.c_str());

        // TODO: parse each individual instruction's registers, ABC etc.
        switch(opcode) {
        case LOP_NOP:
        case LOP_BREAK:
            break;
        case LOP_LOADNIL:
            break;
        }
    }

    for (int i = 0; i < p->sizep; i++) {
        this->processProto(p->p[i], p);
    }
}

bool Disassembler::disassemble() {
    lua_State* L = luaL_newstate();

    if (luau_load(L, "=Script", this->inputBytecode.c_str(), this->inputBytecode.size(), 0)) {
        return false;
    }

    // our bytecode has now been parsed and we can traverse the instructions in the protos it has created.
    Closure* mainClosure = clvalue(L->top - 1);

    this->processProto(mainClosure->l.p, nullptr);

    return true;
}

std::string Disassembler::getStreamData() {
    return this->stream.str();
}