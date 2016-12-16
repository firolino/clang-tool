#include "functioncallworker.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Rewrite/Core/Rewriter.h>

FunctionCallWorker::FunctionCallWorker(clang::ASTContext &context, clang::Rewriter &rewriter)
    : Worker(context, rewriter)
{}

void FunctionCallWorker::start()
{
    using namespace clang::ast_matchers;

    MatchFinder functionFinder;

    auto callExprMatcher = callExpr().bind("callExpr");
    functionFinder.addMatcher(callExprMatcher, this);

    functionFinder.matchAST(context);
}

void FunctionCallWorker::run(const clang::ast_matchers::MatchFinder::MatchResult &result)
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

void FunctionCallWorker::print(clang::raw_ostream &stream)
{
    for(auto &fn : functions)
        stream << fn << "(..)\n";
}

