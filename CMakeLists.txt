cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(luau_disasm LANGUAGES CXX)

add_executable(luau-disasm)

include(sources.cmake)