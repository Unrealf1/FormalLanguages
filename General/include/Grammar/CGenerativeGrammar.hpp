#ifndef FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_
#define FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_

#include <vector>
#include "CRule.hpp"
#include "IGrammar.hpp"

namespace formals { namespace grammars {

    class GenerativeGrammarIterator: public std::iterator<std::input_iterator_tag, CRule>
    {
        friend class CGenerativeGrammar;
    public:
        GenerativeGrammarIterator(const GenerativeGrammarIterator &it);

        bool operator!=(GenerativeGrammarIterator const& other) const;
        bool operator==(GenerativeGrammarIterator const& other) const;
        typename GenerativeGrammarIterator::reference operator*() const;
        GenerativeGrammarIterator& operator++();
    private:
        GenerativeGrammarIterator(CRule* pointer);
        CRule* pointer;
    };

    class CGenerativeGrammar : public IGrammar
    {
    public:
        typedef GenerativeGrammarIterator iterator;

        CGenerativeGrammar() = default;
        virtual ~CGenerativeGrammar() = default;

        virtual iterator begin();
        virtual iterator end();

        virtual void AddRule(const CRule& rule);
    private:
        std::vector<CRule> rules_;
    };
}}


#endif  // FORMALS_GENERAL_GRAMMAR_CGENERATIVEGRAMMAR_HPP_