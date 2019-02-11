#include "Grammar/CRule.hpp"
namespace formals
{
    namespace grammars
    {
    CRule::CRule (const std::vector<RuleSymbol>& left_part, 
            const std::vector<RuleSymbol>& right_part)
            :left_part(left_part), right_part(right_part) {}
    }
}