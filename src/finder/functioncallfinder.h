#ifndef FUNCTIONCALL_FINDER_HPP
#define FUNCTIONCALL_FINDER_HPP

#include "finder.h"

#include <string>
#include <vector>

namespace clang
{
    class ASTContext;
    class raw_ostream;
}

class FunctionCallFinder : public Finder
{
    private:
        
        std::vector<std::string> functions;
        
    public:

        explicit FunctionCallFinder(clang::ASTContext &context);

        virtual void startSearch() override;
        virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &result);
        virtual void print(clang::raw_ostream &stream) override;
};


#endif
