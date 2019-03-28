#ifndef FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_
#define FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_

#include <memory>
#include <cinttypes>
#include <unordered_set>
#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include "ErrorHelper.h"
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/CRule.hpp"
#include "Grammar/Serialization/CGrammarRepresenter.h"

namespace formals { namespace grammars {
    enum class ReadMode {
        binary, text
    };

    namespace parameters {

        const std::string kNoNumbersString = "NoNumbers";
        const std::string kNoStartingString = "NoStarting";
    }

    const std::string kTerminalsKeyLine = "Terminals";
    const std::string kNonTerminalsKeyLine = "Non-terminals";
    const std::string kRulesKeyLine = "Rules";
    const std::string kParametersKeyLine = "Parameters";

    class CGrammarDeserializer
    {
        public:
            CGrammarDeserializer(
                    std::istream& stream,
                    ReadMode mode);
            explicit CGrammarDeserializer(std::istream& stream);
            std::shared_ptr<CGenerativeGrammar> GetGrammar();
            std::shared_ptr<CGrammarRepresenter> GetRepresenter();
        private:
            std::shared_ptr<CGenerativeGrammar> my_grammar_;
            std::shared_ptr<CGrammarRepresenter> my_grammar_representer_;
            std::istream& stream_;
            ReadMode mode_;

            /*
             * This two methods use stream given in constructor and attempt to deserialize
             * grammar from it. On success pointer to grammar is returned.
             * On failure nullptr is returned. They assume, that my_grammar_ is empty and exists
            */
            std::shared_ptr<CGenerativeGrammar> binaryDecode();
            std::shared_ptr<CGenerativeGrammar> textDecode();

            /*Extracts number from key line (like "Terminals(5):")*/
            ssize_t getNumberFromText(const std::string&) const;

            /* Extracts pne rule from the stream and add necessary
             * information to my_grammar and my_grammar_representer_*/
            void readRule(
                    const std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                    const std::unordered_set<ruleSymbolValyeType>& terminals,
                    const std::unordered_set<ruleSymbolValyeType>& starting) const;


            /* This functions read {number} of terminals/non-terminals/rules from
             * stream and add necessary information to my_grammar and my_grammar_representer_*/
            bool readTerminals(
                    std::unordered_map<ruleSymbolValyeType, std::string>& dict,
                    std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                    std::unordered_set<ruleSymbolValyeType>& terminals,
                    size_t number) const;
            bool readNonTerminals(
                    std::unordered_map<ruleSymbolValyeType, std::string>& dict,
                    std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                    std::unordered_set<ruleSymbolValyeType>& starting,
                    size_t number) const;
            bool readRules(
                    const std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                    const std::unordered_set<ruleSymbolValyeType>& terminals,
                    const std::unordered_set<ruleSymbolValyeType>& starting,
                    size_t number) const;


            /* This functions read terminals/non-terminals from stream until encounter a key string
             * and add necessary information to my_grammar and my_grammar_representer_
             */
            bool readTerminals(
                    std::unordered_map<ruleSymbolValyeType, std::string>& dict,
                    std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                    std::unordered_set<ruleSymbolValyeType>& terminals) const;
            bool readNonTerminals(
                    std::unordered_map<ruleSymbolValyeType, std::string>& dict,
                    std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                    std::unordered_set<ruleSymbolValyeType>& starting) const;

            /*This functions read rules from stream while it can and add necessary
             * information to my_grammar and my_grammar_representer_*/
            bool readRules(
                    const std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                    const std::unordered_set<ruleSymbolValyeType>& terminals,
                    const std::unordered_set<ruleSymbolValyeType>& starting) const;

        bool GetTerminals (
                std::string& current_line,
                bool no_numbers,
                bool no_starting,
                std::unordered_map<ruleSymbolValyeType, std::string>& dict,
                std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                std::unordered_set<ruleSymbolValyeType>& terminals);

        bool GetNonTerminals (
                std::string& current_line,
                bool no_numbers,
                bool no_starting,
                std::unordered_map<ruleSymbolValyeType, std::string>& dict,
                std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                std::unordered_set<ruleSymbolValyeType>& starting);

        bool GetRules (
                std::string& current_line,
                bool no_numbers,
                bool no_starting,
                const std::unordered_map<ruleSymbolValyeType, std::string>& dict,
                const std::unordered_map<std::string, ruleSymbolValyeType>& reverse_dict,
                const std::unordered_set<ruleSymbolValyeType>& terminals,
                const std::unordered_set<ruleSymbolValyeType>& starting);

    };

}}

#endif  // FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_