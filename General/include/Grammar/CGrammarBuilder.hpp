#ifndef FORMALS_GENERAL_GRAMMAR_CGRAMMARBUILDER_HPP_
#define FORMALS_GENERAL_GRAMMAR_CGRAMMARBUILDER_HPP_

#include "IGrammar.hpp"
#include <memory>
namespace formals { namespace grammars {
    
    class CGrammarBuilder
    {
    private:
        std::weak_ptr<IGrammar> my_grammar;
    public:
        CGrammarBuilder() = default;
        ~CGrammarBuilder() = default;

        CSpacePizza *GetGrammar();

        void AddRule(const CRule& rule);
    };
}}

#endif  // FORMALS_GENERAL_GRAMMAR_CGRAMMARBUILDER_HPP_