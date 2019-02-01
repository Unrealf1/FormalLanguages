#ifndef FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_
#define FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_

#include "IGrammar.hpp"

namespace formals { namespace grammars {

    class CGenerativeGrammar : public IGrammar
    {
    public:
        virtual ~CGenerativeGrammar() = default;
        virtual std::forward_iterator_tag GetRuleIterator();

    protected:
        CGenerativeGrammar() = default;
        virtual AddRule(const CRule& rule);
    } 
}}


#endif  // FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_