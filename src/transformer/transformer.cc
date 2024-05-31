#include "transformer.h"
#include <clang/Rewrite/Core/Rewriter.h>

Transformer::Transformer(clang::ASTContext &context, clang::Rewriter &rewriter) : context(context), rewriter(rewriter)
{
}
