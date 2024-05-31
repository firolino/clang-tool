#include "integervariablefinder.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>

IntegerVariableFinder::IntegerVariableFinder(clang::ASTContext &context) : Finder(context)
{
}

void IntegerVariableFinder::start()
{
    using namespace clang::ast_matchers;

    MatchFinder integerFinder;

    auto intVarMatcher = varDecl(hasType(isInteger())).bind("intVar");
    integerFinder.addMatcher(intVarMatcher, this);

    integerFinder.matchAST(context);
}

void IntegerVariableFinder::run(const clang::ast_matchers::MatchFinder::MatchResult &result)
{
    using namespace clang;

    if (const VarDecl *varDecl = result.Nodes.getNodeAs<VarDecl>("intVar"))
    {
        if (result.SourceManager->isInSystemHeader(varDecl->getSourceRange().getBegin()))
            return;

        auto intVarName = varDecl->getNameAsString();

        if (intVarName.empty())
            return;

        llvm::outs() << "integer variable: " << varDecl->getNameAsString() << "\n";
    }
}
