#ifndef FORMALS_GENERAL_GRAMMAR_IGRAMMAR_HPP_
#define FORMALS_GENERAL_GRAMMAR_IGRAMMAR_HPP_

#include <iterator>

namespace formals { namespace grammars {

    class IGrammar
    {
    public:
        IGrammar() = default;
        virtual ~IGrammar() = default;
        virtual std::forward_iterator_tag GetRuleIterator() = 0;
        virtual void AddRule(const CRule& rule) = 0;        
    };
}}

#endif  // FORMALS_GENERAL_GRAMMAR_CRULE_HPP_