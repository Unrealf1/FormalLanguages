#include "Grammar/Serialization/CGrammarDeserializer.hpp"

namespace formals { namespace grammars {
        #define GRAMMAR_DES_BINARY 0
        #define GRAMMAR_DES_TEXT 1

        CGrammarDeserializer::CGrammarDeserializer(std::istream& stream, mode_t mode)
            :stream_(stream), mode_(mode) {}

        CGrammarDeserializer::CGrammarDeserializer(std::istream& stream)
            :stream_(stream), mode_(GRAMMAR_DES_BINARY) {}



        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::binary_decode() {
            my_grammar_ = std::make_shared<CGenerativeGrammar>();

            CRule new_rule(std::vector<RuleSymbol>({}), std::vector<RuleSymbol>({}));
            my_grammar_->AddRule(new_rule);                
        }

        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::text_decode() {
            return nullptr;              
        }


        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::GetGrammar() {
            if (my_grammar_ == nullptr) {
                if (mode_ == GRAMMAR_DES_BINARY) {
                    my_grammar_ = binary_decode();
                }
                else if (mode_ == GRAMMAR_DES_TEXT) {
                    my_grammar_ = text_decode();
                }
                
            }

            return my_grammar_;
    }

}}