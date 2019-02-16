#include <iostream>
#include <vector>
#include <memory>
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/Serialization/CGrammarDeserializer.hpp"

int main() {
    //formals::grammars::CGrammarDeserializer deser(std::cin);
    //std::shared_ptr<formals::grammars::CGenerativeGrammar> fake_gr = deser.GetGrammar();
    formals::grammars::CGenerativeGrammar grammar;  
    grammar.begin();
    grammar.end();
    for (int i = 0; i < 5; ++i) {
        grammar.AddRule(formals::grammars::CRule(
            std::vector<formals::grammars::RuleSymbol>({{1, false}, {2, true}, {3, false}}),
            std::vector<formals::grammars::RuleSymbol>({{1, false}, {2, true}, {3, false}})));
    }
    std::cout << "I am working, and grammar is located here: " << &grammar << std::endl;
    std::cout << "begin returned something with address " << &(*(grammar.begin())) << '\n'
    << "while end returned something with address " << &(*(grammar.end())) << '\n';
    size_t n = 0;
    auto it = grammar.begin();
    while (it != grammar.end()) {
        ++n;
        ++it;
    }
    std::cout << "Grammar has " << n << " rules, but for real: " << grammar.Size() << "\n"; 
}