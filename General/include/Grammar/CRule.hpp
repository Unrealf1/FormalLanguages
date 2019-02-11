#ifndef FORMALS_GENERAL_GRAMMAR_CRULE_HPP_
#define FORMALS_GENERAL_GRAMMAR_CRULE_HPP_

#include <vector>
#include <cstdint>

namespace formals { namespace grammars {
    
    struct RuleSymbol {
        uint32_t value;
        bool is_terminal;
    }

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

#endif  // FORMALS_GENERAL_GRAMMAR_CRULE_HPP_