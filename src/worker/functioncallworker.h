#ifndef FUNCTIONCALL_WORKER_HPP
#define FUNCTIONCALL_WORKER_HPP

#include "worker.h"

#include <string>
#include <vector>

namespace clang
{
    class ASTContext;
    class raw_ostream;
    class Rewriter;
}

class FunctionCallWorker : public Worker
{
    private:
        
        std::vector<std::string> functions;
        
    public:

        explicit FunctionCallWorker(clang::ASTContext &context, clang::Rewriter &rewriter);

        virtual void start() override;
        virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &result);
        virtual void print(clang::raw_ostream &stream) override;
};


#endif
