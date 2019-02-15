#include "Grammar/Serialization/CGrammarDeserializer.hpp"

namespace formals { namespace grammars {


        CGrammarDeserializer::CGrammarDeserializer(std::istream& stream)
            :stream_(stream) {}

        std::shared_ptr<CGenerativeGrammar> CGrammarDeserializer::GetGrammar() {
            if (my_grammar_ == nullptr) {
                my_grammar_ = std::make_shared<CGenerativeGrammar>();

                //

                CRule new_rule(std::vector<RuleSymbol>({}), std::vector<RuleSymbol>({}));
                my_grammar_->AddRule(new_rule);                
            }

            return my_grammar_;
    }

}}