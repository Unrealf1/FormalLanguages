#include "Grammar/CGenerativeGrammar.hpp"

namespace formals { namespace grammars {

        std::forward_iterator_tag CGenerativeGrammar::GetRuleIterator() {
            //return rules_.begin();
        }

        void CGenerativeGrammar::AddRule(const CRule& rule) {
            rules_.push_back(rule);
        }
}}
