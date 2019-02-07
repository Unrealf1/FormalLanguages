#include <iostream>
#include <vector>
#include "Grammar/CGenerativeGrammar.hpp"

int main() {
    formals::grammars::CGenerativeGrammar grammar;
    grammar.begin();
    grammar.end();
    grammar.AddRule(formals::grammars::CRule(std::vector<unsigned int>({1, 2, 3}), std::vector<unsigned int>({1, 2, 3}), true));
    std::cout << "I am working, and grammar is located here: " << &grammar << std::endl;
}