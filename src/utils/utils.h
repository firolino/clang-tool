#ifndef CLANG_TOOL_UTILS_H
#define CLANG_TOOL_UTILS_H

#include <fstream>
#include <vector>
#include <string>

#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/Twine.h>

#include <clang/Tooling/Tooling.h>
#include <clang/Frontend/FrontendActions.h>

namespace utils
{
    std::vector<std::string> getSyntaxOnlyToolArgs(const std::vector<std::string> &ExtraArgs, llvm::StringRef FileName);

    bool customRunToolOnCodeWithArgs(clang::FrontendAction *frontendAction, const llvm::Twine &Code,
                                     const std::vector<std::string> &Args, const llvm::Twine &FileName,
                                     const clang::tooling::FileContentMappings &VirtualMappedFiles = clang::tooling::FileContentMappings());


    bool fileExists(const std::string &file);
    std::vector<std::string> getCompileArgs(std::vector<clang::tooling::CompileCommand> compileCommands);
    std::string getSourceCode(const std::string &sourceFile);
}

#endif
