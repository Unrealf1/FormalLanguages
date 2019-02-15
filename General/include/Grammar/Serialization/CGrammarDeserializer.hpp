#ifndef FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_
#define FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_

#include <memory>
#include <istream>
#include <unordered_set>
#include <string>
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/CRule.hpp"

namespace formals { namespace grammars {

    class CGrammarDeserializer
    {
        public:
            CGrammarDeserializer(std::istream& stream);
            std::shared_ptr<CGenerativeGrammar> GetGrammar(); 
        private:
            std::shared_ptr<CGenerativeGrammar> my_grammar_;
            std::istream& stream_;
    };

}}

#endif  // FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_