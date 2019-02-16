#ifndef FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_
#define FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_

#include <memory>
#include <cinttypes>
#include <istream>
#include <unordered_set>
#include <string>
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/CRule.hpp"

namespace formals { namespace grammars {

    class CGrammarDeserializer
    {
        using mode_t = uint16_t;
        public:
            CGrammarDeserializer(std::istream& stream, uint16_t mode);
            CGrammarDeserializer(std::istream& stream);
            std::shared_ptr<CGenerativeGrammar> GetGrammar(); 
        private:
            std::shared_ptr<CGenerativeGrammar> my_grammar_;
            std::istream& stream_;
            mode_t mode_;

            std::shared_ptr<CGenerativeGrammar> binary_decode();
            std::shared_ptr<CGenerativeGrammar> text_decode();
    };

}}

#endif  // FORMALS_GENERAL_SERIALIZATION_CGAMMARDESERIALIZER_HPP_