#ifndef FINDER_HPP
#define FINDER_HPP

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace clang
{
    class ASTContext;
    class raw_ostream;
    class Rewriter;
} // namespace clang

class Finder : public clang::ast_matchers::MatchFinder::MatchCallback
{
  protected:
    clang::ASTContext &context;

  public:
    explicit Finder(clang::ASTContext &context);
    virtual void start() = 0;
};

#endif
