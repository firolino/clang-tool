#include "functioncallfinder.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>

FunctionCallFinder::FunctionCallFinder(clang::ASTContext &context)
    : Finder(context)
{}

void FunctionCallFinder::startSearch()
{
    using namespace clang::ast_matchers;

    MatchFinder functionFinder;

    auto callExprMatcher = callExpr().bind("callExpr");
    functionFinder.addMatcher(callExprMatcher, this);

    functionFinder.matchAST(context);
}

void FunctionCallFinder::run(const clang::ast_matchers::MatchFinder::MatchResult &result)
{
    using namespace clang;

    if(const CallExpr *callExpr = result.Nodes.getNodeAs<CallExpr>("callExpr"))
    {
        if(const FunctionDecl *function = callExpr->getDirectCallee())
        {
            if(result.SourceManager->isInSystemHeader(function->getSourceRange().getBegin()))
                return;
                
            functions.push_back(function->getNameAsString());
        }
    }
}

void FunctionCallFinder::print(clang::raw_ostream &stream)
{
    for(auto &fn : functions)
        stream << fn << "(..)\n";
}

