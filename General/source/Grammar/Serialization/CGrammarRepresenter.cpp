//
// Created by fedor on 3/16/19.
//

#include "Grammar/Serialization/CGrammarRepresenter.h"

namespace formals { namespace grammars {
    CGrammarRepresenter::CGrammarRepresenter (
            std::unordered_map<ruleSymbolValyeType, std::string>&& dict)
            : dict_(std::move(dict)){ }

    void CGrammarRepresenter::ScanGrammar(
            formals::grammars::CGenerativeGrammar &grammar,
            std::unordered_set<ruleSymbolValyeType>& terminals,
            std::unordered_set<ruleSymbolValyeType>& non_terminals,
            std::unordered_set<ruleSymbolValyeType>& starting) const {
        for (auto& rule : grammar) {
            for (auto symbol : rule.left_part) {
                if (symbol.is_terminal) {
                    terminals.insert(symbol.value);
                }
                else {
                    non_terminals.insert(symbol.value);
                    if (symbol.is_starting) {
                        starting.insert(symbol.value);
                    }
                }
            }

            for (auto symbol : rule.right_part) {
                if (symbol.is_terminal) {
                    terminals.insert(symbol.value);
                }
                else {
                    non_terminals.insert(symbol.value);
                    if (symbol.is_starting) {
                        starting.insert(symbol.value);
                    }
                }
            }
        }
    }

    bool CGrammarRepresenter::Represent(
            CGenerativeGrammar& grammar,
            std::ostream& os) {

        std::unordered_set<ruleSymbolValyeType> terminals;
        std::unordered_set<ruleSymbolValyeType> non_terminals;
        std::unordered_set<ruleSymbolValyeType> starting;
        ScanGrammar(grammar, terminals, non_terminals, starting);

        os << "Terminals(" << terminals.size() << "):\n";

        for (auto& symbol : terminals) {
            os << dict_[symbol] << '\n';
        }

        os << "Non-terminals(" << non_terminals.size() << "):\n";
        for (auto& symbol : non_terminals) {
            os << dict_[symbol];
            if (starting.find(symbol) != starting.end()) {
                os << " S";
            }
            os << '\n';
        }

        os << "Rules(" << non_terminals.size() << "):\n";
        for (auto& rule : grammar) {
            for (auto& item : rule.left_part) {
                os << dict_[item.value] << ' ';
            }
            os << "- ";
            for (auto& item : rule.right_part) {
                os << dict_[item.value] << ' ';
            }
            os << '\n';
        }
        std::flush(os);
        return true;
    }
}}