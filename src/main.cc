#include <clang/Tooling/ArgumentsAdjusters.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include "actions/frontendaction.h"

using namespace clang::tooling;

int main(int argc, const char **argv)
{
    llvm::cl::OptionCategory ctCategory("clang-tool options");
    auto expectedParser = CommonOptionsParser::create(argc, argv, ctCategory);
    if (!expectedParser)
    {
        llvm::errs() << expectedParser.takeError();
        return 1;
    }

    CommonOptionsParser &optionsParser = expectedParser.get();
    ClangTool tool(optionsParser.getCompilations(), optionsParser.getSourcePathList());
    tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-resource-dir=" CLANG_RESOURCE_DIR,
                                                           ArgumentInsertPosition::BEGIN));
    return tool.run(newFrontendActionFactory<XFrontendAction>().get());
}
