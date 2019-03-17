#ifndef FORMALS_GENERAL_GRAMMAR_CRULE_HPP_
#define FORMALS_GENERAL_GRAMMAR_CRULE_HPP_

#include <vector>
#include <cstdint>

namespace formals { namespace grammars {

    using ruleSymbolValyeType = size_t;

    struct RuleSymbol {
        ruleSymbolValyeType value;
        bool is_terminal;
        bool is_starting;
    };

    struct CRule
    {
    public:
        CRule (const std::vector<RuleSymbol>& left_part, 
            const std::vector<RuleSymbol>& right_part);
        ~CRule() = default;

        const std::vector<RuleSymbol> left_part;
        const std::vector<RuleSymbol> right_part;
    };
}}

namespace std {

    template<>
    class hash<formals::grammars::CRule> {
    public:
        size_t operator()(const formals::grammars::CRule& rule) const
        {
            size_t hash_const = (rule.left_part.size() + rule.right_part.size())/33 + 1;
            size_t res = 0;
            for (auto i : rule.left_part) {
                res += i.value - hash_const * i.is_terminal + i.is_starting;
                res *= hash_const;
            }
            for (auto i : rule.right_part) {
                res += i.value - hash_const * i.is_terminal + i.is_starting;
                res *= hash_const;
            }

            return res;
        }
    };
}

#endif  // FORMALS_GENERAL_GRAMMAR_CRULE_HPP_