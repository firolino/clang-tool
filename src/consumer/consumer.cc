#include "consumer.h"

#include "../finder/functioncallfinder.h"

XConsumer::XConsumer(clang::ASTContext &context)
{}

void XConsumer::HandleTranslationUnit(clang::ASTContext &context)
{
    rewriter.setSourceMgr(context.getSourceManager(), context.getLangOpts());
    
    FunctionCallFinder fnfinder(context);
    
    fnfinder.startSearch();
    fnfinder.print(llvm::outs());

    auto buffer = rewriter.getRewriteBufferFor(context.getSourceManager().getMainFileID());

    if(buffer != nullptr)
        buffer->write(llvm::outs());
}


