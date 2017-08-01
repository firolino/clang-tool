# clang-tool
clang-tool is a simple and powerful project template for clang-based tools using libtooling[1]. It helps getting started to write standalone tools useful for refactoring, static code analysis, auto-completion etc.

## Installation
Install the necessary llvm and clang headers and libraries for you system an run:

```bash
git clone https://github.com/firolino/clang-tool
cd clang-tool
mkdir build
cd build
cmake ..
make
```

## Usage
A simple example is included in src/transformers/functioncalltransformer.cc that rewriters all function calls from ```functionName()``` to ```fn_functionName()```.

```bash
bin/clang-tool ../examples/simple.cc -- -std=c++11
```


compiler arguments
- direct
- via cdb
- makefiles

# References
[1] http://clang.llvm.org/docs/LibTooling.html


