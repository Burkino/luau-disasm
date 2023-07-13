target_sources(luau-disasm PRIVATE
    src/main.cpp
    src/ArgParser.cpp
    src/Compiler.cpp
    src/Disassembler.cpp

    lib/Luau/Ast.cpp
    lib/Luau/Confusables.cpp
    lib/Luau/Lexer.cpp
    lib/Luau/Location.cpp
    lib/Luau/Parser.cpp
    lib/Luau/StringUtils.cpp
    lib/Luau/TimeTrace.cpp
    
    lib/Luau/BytecodeBuilder.cpp
    lib/Luau/Compiler.cpp
    lib/Luau/Builtins.cpp
    lib/Luau/BuiltinFolding.cpp
    lib/Luau/ConstantFolding.cpp
    lib/Luau/CostModel.cpp
    lib/Luau/TableShape.cpp
    lib/Luau/Types.cpp
    lib/Luau/ValueTracking.cpp
    lib/Luau/lcode.cpp

    lib/Luau/lapi.cpp
    lib/Luau/laux.cpp
    lib/Luau/lbaselib.cpp
    lib/Luau/lbitlib.cpp
    lib/Luau/lbuiltins.cpp
    lib/Luau/lcorolib.cpp
    lib/Luau/ldblib.cpp
    lib/Luau/ldebug.cpp
    lib/Luau/ldo.cpp
    lib/Luau/lfunc.cpp
    lib/Luau/lgc.cpp
    lib/Luau/lgcdebug.cpp
    lib/Luau/linit.cpp
    lib/Luau/lmathlib.cpp
    lib/Luau/lmem.cpp
    lib/Luau/lnumprint.cpp
    lib/Luau/lobject.cpp
    lib/Luau/loslib.cpp
    lib/Luau/lperf.cpp
    lib/Luau/lstate.cpp
    lib/Luau/lstring.cpp
    lib/Luau/lstrlib.cpp
    lib/Luau/ltable.cpp
    lib/Luau/ltablib.cpp
    lib/Luau/ltm.cpp
    lib/Luau/ludata.cpp
    lib/Luau/lutf8lib.cpp
    lib/Luau/lvmexecute.cpp
    lib/Luau/lvmload.cpp
    lib/Luau/lvmutils.cpp
)

target_include_directories(luau-disasm PRIVATE
    include/
    include/Luau
)