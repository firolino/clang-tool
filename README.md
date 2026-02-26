# clang-tool

A project template for building standalone Clang-based tools using [LibTooling](https://clang.llvm.org/docs/LibTooling.html). It helps getting started writing tools for refactoring, static code analysis, auto-completion, and more.

## Requirements

- LLVM and Clang development headers and libraries (tested with LLVM 21)
- CMake 3.20+

## Building

```bash
git clone https://github.com/firolino/clang-tool
cd clang-tool
mkdir build && cd build
cmake ..
make
```

## Usage

The included `FunctionCallTransformer` (`src/transformer/functioncalltransformer.cc`) rewrites all function calls from `functionName()` to `fn_functionName()`:

```bash
bin/clang-tool ../examples/simple.cc -- -std=c++17
```

Output:
```
print(..)
#include <iostream>
using namespace std;

int bad_global = -1;

void fn_print()
{
    cout << "hallo" << endl;
    int variable = 0;
}

int main()
{
    fn_print();
    fn_print();
    ...
}
```

Multiple source files are supported:
```bash
bin/clang-tool s1.cc s2.cc -- -std=c++17
```

### Specifying compiler arguments

There are multiple ways to provide compiler arguments:

- **Direct** — place them after `--`, as shown above.

- **Compilation Database** — if your project uses CMake, pass `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` to generate a `compile_commands.json`. With this file present, `--` is not needed — clang-tool picks it up automatically.

- **Makefiles** — use [Bear](https://github.com/rizsotto/Bear) to generate a `compile_commands.json` from a Makefile project: `bear -- make` on a clean build.

## Architecture

The processing pipeline: **main.cc → FrontendAction → Consumer → Transformer / Finder**

- **`src/main.cc`** — Parses CLI args, creates a `ClangTool`, and runs it.
- **`src/consumer/consumer.cc`** — `XConsumer::HandleTranslationUnit()` wires up which transformers and finders run on each AST.
- **`src/transformer/`** — Base class `Transformer` wraps `ASTContext` + `Rewriter`. Subclasses implement `start()` (register AST matchers) and `run()` (match callback).
- **`src/finder/`** — Base class `Finder` wraps `ASTContext` (read-only, no rewriting). Same `start()`/`run()` pattern.

### Adding a new pass

1. Create a class inheriting from `Transformer` (rewriting) or `Finder` (read-only analysis).
2. Implement `start()` to register [AST matchers](https://clang.llvm.org/docs/LibASTMatchersReference.html) and `run()` as the match callback.
3. Instantiate it in `XConsumer::HandleTranslationUnit()` in `src/consumer/consumer.cc`.

Example — to also print all integer variable declarations, uncomment in `consumer.cc`:

```cpp
IntegerVariableFinder intFinder(context);
intFinder.start();
```

## License

MIT
