cmake_minimum_required(VERSION 2.8)

project(clang-tool)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/)

execute_process (
    COMMAND bash -c "clang++ -E -x c++ - -v < /dev/null 2>&1 | grep \"lib/clang\" | awk '{{print $1}}' | grep include"
    OUTPUT_VARIABLE clangBuiltInIncludePath
)

file(WRITE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/builtInInclude.path" "${clangBuiltInIncludePath}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
add_subdirectory(src)



