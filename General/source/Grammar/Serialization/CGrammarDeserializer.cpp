#include "Grammar/Serialization/CGrammarDeserializer.hpp"


namespace formals { namespace grammars {
        #define GRAMMAR_DES_BINARY 0
        #define GRAMMAR_DES_TEXT 1

        CGrammarDeserializer::CGrammarDeserializer(std::istream& stream, mode_t mode)
            :stream_(stream), mode_(mode) {}

        CGrammarDeserializer::CGrammarDeserializer(std::istream& stream)
            :stream_(stream), mode_(GRAMMAR_DES_BINARY) {}



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
                std::unordered_set<std::string>& terminals,
                size_t number) const {
            formals::errors::ReportError(errors::not_implemented);
            return false;
        }

        bool CGrammarDeserializer::readNonTerminals(
                std::unordered_map<ruleSymbolValyeType, std::string> dict,
                std::unordered_set<std::string>& non_terminals,
                std::unordered_set<std::string>& starting,
                size_t number) const {
            formals::errors::ReportError(errors::not_implemented);
            return false;

        }

        bool CGrammarDeserializer::readRules(
                std::unordered_set<std::string>& terminals,
                std::unordered_set<std::string>& non_terminals,
                std::unordered_set<std::string>& starting,
                size_t number) const {
            formals::errors::ReportError(errors::not_implemented);
            return false;

        }

        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::textDecode() {
            std::string current_line;
            std::unordered_map<ruleSymbolValyeType, std::string> dict;

            std::getline(stream_, current_line);
            ssize_t number_of_terminals = getNumberFromText(current_line);
            if (number_of_terminals == -1) {
                formals::errors::ReportError(formals::errors::ErrorType::wrong_text_format);
                return nullptr;
            }
            std::unordered_set<std::string> terminals;
            if (readTerminals(dict, terminals, number_of_terminals)) {
                formals::errors::ReportError(formals::errors::ErrorType::wrong_text_format);
                return nullptr;
            }

            std::getline(stream_, current_line);
            ssize_t number_of_non_terminals = getNumberFromText(current_line);
            if (number_of_non_terminals == -1) {
                formals::errors::ReportError(formals::errors::ErrorType::wrong_text_format);
                return nullptr;
            }
            std::unordered_set<std::string> non_terminals;
            std::unordered_set<std::string> starting;
            if (readNonTerminals(dict, non_terminals, starting, number_of_non_terminals)) {
                formals::errors::ReportError(formals::errors::ErrorType::wrong_text_format);
                return nullptr;
            }

            std::getline(stream_, current_line);
            ssize_t number_of_rules = getNumberFromText(current_line);
            if (number_of_rules == -1) {
                formals::errors::ReportError(formals::errors::ErrorType::wrong_text_format);
                return nullptr;
            }
            if (readRules(terminals, non_terminals, starting, number_of_rules)) {
                formals::errors::ReportError(formals::errors::ErrorType::wrong_text_format);
                return nullptr;
            }

            return my_grammar_;
        }


        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::GetGrammar() {
            if (my_grammar_ == nullptr) {
                my_grammar_ = std::make_shared<CGenerativeGrammar>();
                my_grammar_representer_.reset();
                if (mode_ == GRAMMAR_DES_BINARY) {
                    my_grammar_ = binaryDecode();
                }
                else if (mode_ == GRAMMAR_DES_TEXT) {
                    my_grammar_ = textDecode();
                }
                else {
                    formals::errors::ReportError(formals::errors::ErrorType::unreachable_code);
                }
            }

            return my_grammar_;
    }

}}