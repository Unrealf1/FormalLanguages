#ifndef FORMALS_GENERAL_GRAMMAR_IGRAMMAR_HPP_
#define FORMALS_GENERAL_GRAMMAR_IGRAMMAR_HPP_

#include <iterator>

namespace formals { namespace grammars {

    class IGrammar
    {
    public:
        virtual ~IGrammar() = default;
        virtual std::forward_iterator_tag GetRuleIterator() = 0;

    protected:
        IGrammar() = default;
        virtual AddRule(const CRule& rule) = 0;
    }
}}

#endif  // FORMALS_GENERAL_GRAMMAR_CRULE_HPP_