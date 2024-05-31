#ifndef FRONTEND_ACTION_HPP
#define FRONTEND_ACTION_HPP

#include <clang/Frontend/FrontendActions.h>
#include <llvm/ADT/StringRef.h>

#include <memory>
#include <string>
#include <vector>

namespace clang
{
    class CompilerInstance;
}

class XFrontendAction : public clang::ASTFrontendAction
{
  public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &compiler,
                                                                  llvm::StringRef inFile) override;
};

#endif
