#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/Serialization/CGrammarDeserializer.hpp"
#include "Grammar/Serialization/CGrammarRepresenter.h"


#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"

int main(int argc, char** argv) {
    //formals::grammars::CGrammarDeserializer deser(std::cin);
    //std::shared_ptr<formals::grammars::CGenerativeGrammar> fake_gr = deser.GetGrammar();
    /*formals::grammars::CGenerativeGrammar grammar;
    grammar.begin();
    grammar.end();
    for (int i = 0; i < 5; ++i) {
        grammar.AddRule(formals::grammars::CRule(
            std::vector<formals::grammars::RuleSymbol>({{1, false, false}, {2, true}, {3, false}}),
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

    */
    if (argc < 2) {
        std::cout << "Please put path to Test directory as first argument" << std::endl;
        return 1;
    }

    std::string path_to_test = argv[1];

    std::ifstream iff (path_to_test + "Samples/Grammars/Text/CBS_1");
    if (iff.fail()) {
        formals::errors::ReportError(
                formals::errors::ErrorType::unreachable_code, "couldn't open the file");
        return 2;
    }
    formals::grammars::CGrammarDeserializer deserializer(iff, formals::grammars::ReadMode::text);
    std::cout << "\nNow please enter yor grammar here:" << std::endl;
    std::shared_ptr<formals::grammars::CGenerativeGrammar> user_grammar = deserializer.GetGrammar();
    std::cout << "Got this:\n";

    std::cout << "Grammar size = " << user_grammar->Size() << "\nRules are:\n";
    for (auto& rule : *user_grammar) {
        for (auto& sym : rule.left_part) {
            std::cout << sym.value;
            if (!sym.is_terminal) {
                std::cout << '*';
                if (sym.is_starting) {
                    std::cout << 'S';
                }
            }
            std::cout << ' ';
        }

        std::cout << "-> ";

        for (auto& sym : rule.left_part) {
            std::cout << sym.value;
            if (!sym.is_terminal) {
                std::cout << '*';
                if (sym.is_starting) {
                    std::cout << 'S';
                }
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }

}
