#ifndef FORMALS_GENERAL_GRAMMAR_CRULE_HPP_
#define FORMALS_GENERAL_GRAMMAR_CRULE_HPP_

#include <vector>
#include <cstdint>

namespace formals { namespace grammars {
    
    struct CRule
    {
    public:
        CRule (const std::vector<uint32_t>& left_part, 
            const std::vector<uint32_t>& right_part, const bool is_terminal);
        ~CRule() = default;

        const bool is_terminal;
        const std::vector<uint32_t> left_part;
        const std::vector<uint32_t> right_part;
    }
}}

#endif  // FORMALS_GENERAL_GRAMMAR_CRULE_HPP_