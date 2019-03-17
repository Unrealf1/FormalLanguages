#include "Grammar/Serialization/CGrammarDeserializer.hpp"


namespace formals { namespace grammars {
                CGrammarDeserializer::CGrammarDeserializer(std::istream& stream, ReadMode mode)
            :stream_(stream), mode_(mode) {}

        CGrammarDeserializer::CGrammarDeserializer(std::istream& stream)
            :stream_(stream), mode_(ReadMode::binary) {}



        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::binaryDecode() {
            my_grammar_ = std::make_shared<CGenerativeGrammar>();

            CRule new_rule(std::vector<RuleSymbol>({}), std::vector<RuleSymbol>({}));
            my_grammar_->AddRule(new_rule);

            formals::errors::ReportError(formals::errors::ErrorType::not_implemented);
            return nullptr;
        }

        ssize_t CGrammarDeserializer::getNumberFromText(
                const std::string& format_string) const {
            auto left_bracket = format_string.begin();
            for (; left_bracket != format_string.end() && *left_bracket != '('; ++left_bracket) {}
            if (left_bracket == format_string.end()) {
                return -1;
            }
            auto right_bracket = format_string.rbegin();
            for (; right_bracket != format_string.rend() && *right_bracket != ')'; ++right_bracket) {}
            if (right_bracket == format_string.rend()) {
                return -1;
            }

            long start = left_bracket - format_string.begin() + 1;

            //not sure here
            long length = right_bracket - format_string.rbegin();

            if (start <= 0 || length <= 0) {
                return -1;
            }

            try {
                return stoll(format_string.substr(start, length), nullptr, 10);
            }
            catch (...) {
                return -1;
            }


        }

        bool CGrammarDeserializer::readTerminals(
                std::unordered_map<ruleSymbolValyeType, std::string> dict,
                std::unordered_map<std::string, ruleSymbolValyeType> reverse_dict,
                std::unordered_set<ruleSymbolValyeType>& terminals,
                size_t number) const {

            for (size_t i = 0; i < number; ++i) {
                std::string terminal;
                std::getline(stream_, terminal);
                ruleSymbolValyeType value = dict.size();
                dict[value] = terminal;
                reverse_dict[terminal] = value;
                terminals.insert(value);
            }

            return true;
        }

        //This function checks if the the line from non-terminal list
        //in plain text grammar format refers to starting non-terminal or not
        bool IsStarting(const std::string& non_terminal_line) {
            return !(non_terminal_line.size() < 2 ||
                     non_terminal_line[non_terminal_line.size() - 2] != '-');
        }

        bool CGrammarDeserializer::readNonTerminals(
                std::unordered_map<ruleSymbolValyeType, std::string> dict,
                std::unordered_map<std::string, ruleSymbolValyeType> reverse_dict,
                std::unordered_set<ruleSymbolValyeType>& non_terminals,
                std::unordered_set<ruleSymbolValyeType>& starting,
                size_t number) const {

            for (size_t i = 0; i < number; ++i) {
                std::string non_terminal_line;
                std::getline(stream_, non_terminal_line);
                std::string non_terminal;
                ruleSymbolValyeType value = dict.size();
                if (IsStarting(non_terminal_line)) {
                    non_terminal = non_terminal_line.substr(0, non_terminal_line.size() - 2);
                    starting.insert(value);
                } else {
                    non_terminal = std::move(non_terminal_line);
                }
                dict[value] = non_terminal;
                reverse_dict[non_terminal] = value;
                non_terminals.insert(value);
            }
            return true;

        }

        void GetRightPartFromLine(
                const std::string& right_part_line,
                std::vector<std::string>& items) {
            (void)right_part_line;
            (void)items;
            formals::errors::ReportError(errors::ErrorType::not_implemented, "GetRightPartFromLine");
        }

        bool CGrammarDeserializer::readRules(
                std::unordered_map<std::string, ruleSymbolValyeType> reverse_dict,
                std::unordered_set<ruleSymbolValyeType>& terminals,
                std::unordered_set<ruleSymbolValyeType>& starting,
                size_t number) const {

            for (size_t i = 0; i < number; ++i) {
                std::vector<RuleSymbol> left_part;
                std::string item;
                stream_ >> item;
                while (item != "-") {
                    RuleSymbol symbol;
                    symbol.value = reverse_dict[item];

                    symbol.is_terminal = (terminals.find(symbol.value) != terminals.end());
                    if (!symbol.is_terminal) {
                        symbol.is_starting = (starting.find(symbol.value) != starting.end());
                    }
                    left_part.push_back(symbol);

                    stream_ >> item;
                }

                std::string right_part_line;
                std::getline(stream_, right_part_line);
                std::vector<std::string> right_items;
                GetRightPartFromLine(right_part_line, right_items);
                std::vector<RuleSymbol> right_part;

                for (auto& right_item : right_items) {
                    RuleSymbol symbol;
                    symbol.value = reverse_dict[right_item];

                    symbol.is_terminal = (terminals.find(symbol.value) != terminals.end());
                    if (!symbol.is_terminal) {
                        symbol.is_starting = (starting.find(symbol.value) != starting.end());
                    }
                    right_part.push_back(symbol);
                }
                my_grammar_->AddRule({left_part, right_part});
            }
            return true;

        }

        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::textDecode() {
            std::string current_line;
            std::unordered_map<ruleSymbolValyeType, std::string> dict;
            std::unordered_map<std::string, ruleSymbolValyeType> reverse_dict;

            std::getline(stream_, current_line);
            ssize_t number_of_terminals = getNumberFromText(current_line);
            if (number_of_terminals == -1) {
                formals::errors::ReportError(
                        formals::errors::ErrorType::wrong_text_format,
                        "Number of terminals");
                return nullptr;
            }
            std::unordered_set<ruleSymbolValyeType > terminals;
            if (!readTerminals(dict, reverse_dict, terminals, number_of_terminals)) {
                formals::errors::ReportError(
                        formals::errors::ErrorType::wrong_text_format,
                        "Terminals section");
                return nullptr;
            }

            std::getline(stream_, current_line);
            ssize_t number_of_non_terminals = getNumberFromText(current_line);
            if (number_of_non_terminals == -1) {
                formals::errors::ReportError(
                        formals::errors::ErrorType::wrong_text_format,
                        "Number of non-terminals");
                return nullptr;
            }
            std::unordered_set<ruleSymbolValyeType> non_terminals;
            std::unordered_set<ruleSymbolValyeType> starting;
            if (!readNonTerminals(dict, reverse_dict, non_terminals, starting, number_of_non_terminals)) {
                formals::errors::ReportError(
                        formals::errors::ErrorType::wrong_text_format,
                        "Non-terminals section");
                return nullptr;
            }

            std::getline(stream_, current_line);
            ssize_t number_of_rules = getNumberFromText(current_line);
            if (number_of_rules == -1) {
                formals::errors::ReportError(
                        formals::errors::ErrorType::wrong_text_format,
                        "Number of rules");
                return nullptr;
            }
            if (!readRules(reverse_dict, terminals, starting, number_of_rules)) {
                formals::errors::ReportError(
                        formals::errors::ErrorType::wrong_text_format,
                        "Rules section");
                return nullptr;
            }

            return my_grammar_;
        }

        std::shared_ptr<CGrammarRepresenter> CGrammarDeserializer::GetRepresenter() {
            errors::ReportError(errors::ErrorType::not_implemented, "GetRepresenter");
            return nullptr;
        }

        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::GetGrammar() {
            if (my_grammar_ == nullptr) {
                my_grammar_ = std::make_shared<CGenerativeGrammar>();
                my_grammar_representer_.reset();
                if (mode_ == ReadMode::binary) {
                    my_grammar_ = binaryDecode();
                }
                else if (mode_ == ReadMode::text) {
                    my_grammar_ = textDecode();
                }
                else {
                    formals::errors::ReportError(formals::errors::ErrorType::unreachable_code);
                }
            }

            return my_grammar_;
        }

}}