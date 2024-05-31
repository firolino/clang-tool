#include "consumer.h"

#include "../finder/integervariablefinder.h"
#include "../transformer/functioncalltransformer.h"

XConsumer::XConsumer(clang::ASTContext &context)
{
}

void XConsumer::HandleTranslationUnit(clang::ASTContext &context)
{
    rewriter.setSourceMgr(context.getSourceManager(), context.getLangOpts());

    FunctionCallTransformer fntransformer(context, rewriter);

    fntransformer.start();
    fntransformer.print(llvm::outs());

    // IntegerVariableFinder intFinder(context);
    // intFinder.start();

    auto buffer = rewriter.getRewriteBufferFor(context.getSourceManager().getMainFileID());

    if (buffer != nullptr)
        buffer->write(llvm::outs());
}
