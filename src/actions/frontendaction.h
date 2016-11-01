#ifndef CLANG_TOOL_FRONTEND_ACTION_HPP
#define CLANG_TOOL_FRONTEND_ACTION_HPP

#include <llvm/ADT/StringRef.h>
#include <clang/Frontend/FrontendActions.h>

#include <memory>
#include <vector>
#include <string>

namespace clang
{
    class CompilerInstance;
}

class XFrontendAction : public clang::ASTFrontendAction 
{
    public:

        virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler, llvm::StringRef inFile) override;
};

#endif
