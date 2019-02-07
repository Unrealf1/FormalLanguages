#include <iostream>
#include <vector>
#include "Grammar/CGenerativeGrammar.hpp"

int main() {
    formals::grammars::CGenerativeGrammar grammar;
    grammar.begin();
    grammar.end();
    for (int i = 0; i < 5; ++i) {
        grammar.AddRule(formals::grammars::CRule(
            std::vector<unsigned int>({1, 2, 3}),
            std::vector<unsigned int>({1, 2, 3}), true));
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