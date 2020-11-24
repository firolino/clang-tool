#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include "actions/frontendaction.h"
#include "utils/utils.h"

#include <string>

using namespace std;
using namespace llvm;
using namespace clang;
using namespace clang::tooling;

int main(int argc, const char **argv)
{
    llvm::cl::OptionCategory ctCategory("clang-tool options");
    CommonOptionsParser optionsParser(argc, argv, ctCategory);

    for(auto &sourceFile : optionsParser.getSourcePathList())
    {
        if(utils::fileExists(sourceFile) == false)
        {
            llvm::errs() << "File: " << sourceFile << " does not exist!\n";
            return -1;
        }

        auto sourcetxt = utils::getSourceCode(sourceFile);
        auto compileCommands = optionsParser.getCompilations().getCompileCommands(getAbsolutePath(sourceFile));

        std::vector<std::string> compileArgs = utils::getCompileArgs(compileCommands);
        compileArgs.push_back("-I" + utils::getClangBuiltInIncludePath(argv[0]));
        for(auto &s : compileArgs)
            llvm::outs() << s << "\n";

        auto xfrontendAction = std::make_unique<XFrontendAction>();
        utils::customRunToolOnCodeWithArgs(move(xfrontendAction), sourcetxt, compileArgs, sourceFile);
    }

    return 0;
}
