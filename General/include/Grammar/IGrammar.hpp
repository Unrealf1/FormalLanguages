#ifndef FORMALS_GENERAL_GRAMMAR_IGRAMMAR_HPP_
#define FORMALS_GENERAL_GRAMMAR_IGRAMMAR_HPP_

#include <iterator>
#include "CRule.hpp"

namespace formals { namespace grammars {

    class IGrammar
    {
    public:
        IGrammar() = default;
        virtual ~IGrammar() = default;

        virtual void AddRule(const CRule& rule) = 0;        
    };
}}

#endif  // FORMALS_GENERAL_GRAMMAR_IGRAMMAR_HPP_