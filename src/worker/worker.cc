#include "worker.h"
#include <clang/Rewrite/Core/Rewriter.h>

Worker::Worker(clang::ASTContext &context, clang::Rewriter &rewriter)
        : context(context), rewriter(rewriter)
{}
