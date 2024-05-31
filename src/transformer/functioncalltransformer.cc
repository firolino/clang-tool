#include "functioncalltransformer.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Rewrite/Core/Rewriter.h>

FunctionCallTransformer::FunctionCallTransformer(clang::ASTContext &context, clang::Rewriter &rewriter)
    : Transformer(context, rewriter)
{
}

void FunctionCallTransformer::start()
{
    using namespace clang::ast_matchers;

    MatchFinder functionFinder;

    auto callExprMatcher = callExpr().bind("callExpr");
    functionFinder.addMatcher(callExprMatcher, this);

    functionFinder.matchAST(context);
}

void FunctionCallTransformer::run(const clang::ast_matchers::MatchFinder::MatchResult &result)
{
    using namespace clang;

    /*
     * CallExpr is the function call
     * FunctionDecl is fhe function definition
     */

    if (const CallExpr *callExpr = result.Nodes.getNodeAs<CallExpr>("callExpr"))
    {
        if (const FunctionDecl *function = callExpr->getDirectCallee())
        {
            if (result.SourceManager->isInSystemHeader(function->getSourceRange().getBegin()))
                return;

            auto functionName = function->getNameAsString();
            rewriter.InsertTextAfter(callExpr->getBeginLoc(), "fn_");

            if (functions.count(functionName) == 0)
            {
                // rewrite definition as well
                rewriter.InsertTextAfter(function->getLocation(), "fn_");
                functions.insert(function->getNameAsString());
            }
        }
    }
}

void FunctionCallTransformer::print(clang::raw_ostream &stream)
{
    for (auto &fn : functions)
        stream << fn << "(..)\n";
}
