#ifndef FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_
#define FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_

#include <memory>
#include <cinttypes>
#include <unordered_set>
#include <string>
#include <cassert>
#include <iostream>
#include "ErrorHelper.h"
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/CRule.hpp"
#include "Grammar/Serialization/CGrammarRepresenter.h"

namespace formals { namespace grammars {

    class CGrammarDeserializer
    {
        using mode_t = uint16_t;
        public:
            CGrammarDeserializer(
                    std::istream& stream,
                    uint16_t mode);
            explicit CGrammarDeserializer(std::istream& stream);
            std::shared_ptr<CGenerativeGrammar> GetGrammar();
            std::shared_ptr<CGrammarRepresenter> GetRepresenter();
        private:
            std::shared_ptr<CGenerativeGrammar> my_grammar_;
            std::shared_ptr<CGrammarRepresenter> my_grammar_representer_;
            std::istream& stream_;
            mode_t mode_;

            /*
             * This two methods use stream given in constructor and attempt to deserialize
             * grammar from it. On success pointer to grammar is returned.
             * On failure nullptr is returned. They assume, that my_grammar_ is empty and exists
            */
            std::shared_ptr<CGenerativeGrammar> binaryDecode();
            std::shared_ptr<CGenerativeGrammar> textDecode();

            ssize_t getNumberFromText(const std::string&) const;
            bool readTerminals(
                    std::unordered_map<ruleSymbolValyeType, std::string> dict,
                    std::unordered_set<std::string>& terminals,
                    size_t number) const;
            bool readNonTerminals(
                    std::unordered_map<ruleSymbolValyeType, std::string> dict,
                    std::unordered_set<std::string>& non_terminals,
                    std::unordered_set<std::string>& starting,
                    size_t number) const;
            bool readRules(
                    std::unordered_set<std::string>& terminals,
                    std::unordered_set<std::string>& non_terminals,
                    std::unordered_set<std::string>& starting,
                    size_t number) const;
    };

}}

#endif  // FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_