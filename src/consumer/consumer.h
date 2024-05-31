#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/Rewrite/Core/Rewriter.h>

namespace clang
{
    class ASTContext;
}

class XConsumer : public clang::ASTConsumer
{
  private:
    clang::Rewriter rewriter;

  public:
    explicit XConsumer(clang::ASTContext &context);
    virtual void HandleTranslationUnit(clang::ASTContext &context) override;
};

#endif
