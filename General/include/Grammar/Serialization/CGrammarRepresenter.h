//
// Created by fedor on 3/16/19.
//

#ifndef FORMALLANGUAGES_CGRAMMARREPRESENTER_H
#define FORMALLANGUAGES_CGRAMMARREPRESENTER_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cinttypes>
#include <ostream>
#include <vector>
#include <memory>
#include "Grammar/CRule.hpp"
#include "Grammar/CGenerativeGrammar.hpp"
#include "ErrorHelper.h"

namespace formals { namespace grammars {
    class CGrammarRepresenter {
    public:
        CGrammarRepresenter (
                std::unordered_map<ruleSymbolValyeType, std::string>&& dict);
        bool Represent(
                CGenerativeGrammar& grammar,
                std::ostream& os);
        bool Represent(
                std::shared_ptr<CGenerativeGrammar> grammar,
                std::ostream& os);
    private:
        std::unordered_map<ruleSymbolValyeType, std::string> dict_;

        void ScanGrammar(
                formals::grammars::CGenerativeGrammar &grammar,
                std::unordered_set<ruleSymbolValyeType>& terminals,
                std::unordered_set<ruleSymbolValyeType>& non_terminals,
                std::unordered_set<ruleSymbolValyeType>& starting) const;

    };
}}

#endif //FORMALLANGUAGES_CGRAMMARREPRESENTER_H
