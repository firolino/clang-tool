#ifndef NAT_TRANSFORMER_HPP
#define NAT_TRANSFORMER_HPP

#include "transformer.h"

#include <string>
#include <set>

namespace clang
{
    class ASTContext;
    class raw_ostream;
    class Rewriter;
}

class NatTransformer : public Transformer
{
    public:

        explicit NatTransformer(clang::ASTContext &context, clang::Rewriter &rewriter);

        virtual void start() override;
        virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &result);
        virtual void print(clang::raw_ostream &stream) override;
};


#endif
