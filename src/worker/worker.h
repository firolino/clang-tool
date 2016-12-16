#ifndef WORKER_HPP
#define WORKER_HPP

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace clang
{
    class ASTContext;
    class raw_ostream;
}

class Worker : public clang::ast_matchers::MatchFinder::MatchCallback
{
    protected:

        clang::ASTContext &context;

    public:

        explicit Worker(clang::ASTContext &context);
        
        virtual void start() = 0;
        virtual void print(clang::raw_ostream &stream) = 0;
};

#endif
