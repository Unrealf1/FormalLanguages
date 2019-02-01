#include "CRule.hpp"
namespace formals
{
    namespace grammars
    {
    CRule::CRule (const std::vector<uint32_t>& left_part, 
            const std::vector<uint32_t>& right_part, const bool is_terminal)
            :left_part(left_part), right_part(right_part), is_terminal(is_terminal) {}
    }
}