#include "Grammar/CGenerativeGrammar.hpp"

namespace formals { namespace grammars {

        GenerativeGrammarIterator::GenerativeGrammarIterator(CRule *pointer) :
            pointer(pointer) {

        }

        GenerativeGrammarIterator::GenerativeGrammarIterator(const GenerativeGrammarIterator& it) :
            pointer(it.pointer) {

        }

        bool GenerativeGrammarIterator::operator!=(GenerativeGrammarIterator const& other) const
        {
            return pointer != other.pointer;
        }

        bool GenerativeGrammarIterator::operator==(GenerativeGrammarIterator const& other) const
        {
            return pointer == other.pointer;
        }

        typename GenerativeGrammarIterator::reference GenerativeGrammarIterator::operator*() const
        {
            return *pointer;
        }

        GenerativeGrammarIterator &GenerativeGrammarIterator::operator++()
        {
            ++pointer;
            return *this;
        }

        typedef GenerativeGrammarIterator iterator;

        iterator CGenerativeGrammar::begin() {
            return &(*(rules_.begin()));
        }

        iterator CGenerativeGrammar::end() {
            return &(*(rules_.end()));
        }

        void CGenerativeGrammar::AddRule(const CRule& rule) {
            //May be should maintain something(rules with starting)
            rules_.push_back(rule);
        }

        size_t CGenerativeGrammar::Size() const {
            return rules_.size();
        }
}}
