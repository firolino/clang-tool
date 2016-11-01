#ifndef FINDER_HPP
#define FINDER_HPP

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace clang
{
    class ASTContext;
    class raw_ostream;
}

class Finder : public clang::ast_matchers::MatchFinder::MatchCallback
{
    protected:

        clang::ASTContext &context;

    public:

        explicit Finder(clang::ASTContext &context);
        
        virtual void startSearch() = 0;
        virtual void print(clang::raw_ostream &stream) = 0;
};

#endif
