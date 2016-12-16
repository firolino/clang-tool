#include "consumer.h"

#include "../worker/functioncallworker.h"

XConsumer::XConsumer(clang::ASTContext &context)
{}

void XConsumer::HandleTranslationUnit(clang::ASTContext &context)
{
    rewriter.setSourceMgr(context.getSourceManager(), context.getLangOpts());
    
    FunctionCallWorker fnworker(context, rewriter);
        
    fnworker.start();
    fnworker.print(llvm::outs());

    auto buffer = rewriter.getRewriteBufferFor(context.getSourceManager().getMainFileID());

    if(buffer != nullptr)
        buffer->write(llvm::outs());
}


