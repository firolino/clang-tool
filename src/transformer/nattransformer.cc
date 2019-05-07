#include "nattransformer.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Rewrite/Core/Rewriter.h>

NatTransformer::NatTransformer(clang::ASTContext &context, clang::Rewriter &rewriter)
    : Transformer(context, rewriter)
{}

void NatTransformer::start()
{
    using namespace clang::ast_matchers;

    MatchFinder exprFinder;

    auto memberExprMatcher = memberExpr(member(hasName("x"))).bind("memberExpr");
    exprFinder.addMatcher(memberExprMatcher, this);

    exprFinder.matchAST(context);
}

void NatTransformer::run(const clang::ast_matchers::MatchFinder::MatchResult &result)
{
    using namespace clang;
    
    if(const MemberExpr *memExpr = result.Nodes.getNodeAs<MemberExpr>("memberExpr"))
    {
        if(result.SourceManager->isInSystemHeader(memExpr->getSourceRange().getBegin()))
            return;

        llvm::outs() <<  memExpr->getMemberDecl()->getDeclName() << "\n";

        rewriter.InsertText(memExpr->getSourceRange().getBegin(), "getX(");
        rewriter.InsertText(memExpr->getOperatorLoc(), ")");

        // getLocWithOffset(-1): dont remove - from ->
        rewriter.RemoveText(SourceRange(memExpr->getOperatorLoc(), memExpr->getSourceRange().getEnd().getLocWithOffset(-1)));
    }
}

void NatTransformer::print(clang::raw_ostream &stream)
{}

