#ifndef FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_
#define FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_

#include <vector>
#include "CRule.hpp"
#include "IGrammar.hpp"

namespace formals { namespace grammars {

    class CGenerativeGrammar : public IGrammar
    {
    public:
        CGenerativeGrammar() = default;
        virtual ~CGenerativeGrammar() = default;
        virtual std::forward_iterator_tag GetRuleIterator() override;
        virtual void AddRule(const CRule& rule) override;
    private:
        std::vector<CRule> rules_;
    };
}}


#endif  // FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_