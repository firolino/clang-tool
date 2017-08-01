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
A simple example is included in ```src/transformers/functioncalltransformer.cc``` that rewriters all function calls from ```functionName()``` to ```fn_functionName()```.

```bash
bin/clang-tool ../examples/simple.cc -- -std=c++11
```

## Specifiying compiler arguments
There are multiple ways to provide your projects' compiler arguments to a clang tool:

### Direct
As can be seen in the example above, compiler arguments can be placed directly after ```--```.

### Compilation Database
If your project is CMake-based use ```-DCMAKE_EXPORT_COMPILE_COMMANDS=ON``` in your cmake call. It will generate a ```compile_commands.json``` in your build directory containing your compiler arguments etc. With the json file you don't need to provide ```--`` anymore. clang-tool will automatically use your json file:

```bash
bin/clang-tool ../examples/simple.cc
```

### Makefiles
If you have an ordinary Makefile based project, use rizsottos awesome tool from https://github.com/rizsotto/Bear and run ```bear make``` on a cleanded project directory. It will generate a ```compile_commands.json``` for you!

# References
[1] http://clang.llvm.org/docs/LibTooling.html


