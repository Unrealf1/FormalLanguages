#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include "test_main.hpp"
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/Serialization/CGrammarDeserializer.hpp"
#include "Grammar/Serialization/CGrammarRepresenter.h"
#include "gtest/gtest.h"

std::string path_to_test;

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Please put path to Test directory as first argument" << std::endl;
        return 1;
    }

    path_to_test = argv[1];

    std::ifstream iff (path_to_test + "Samples/Grammars/Text/CBS_1");
    if (iff.fail()) {
        formals::errors::ReportError(
                formals::errors::ErrorType::unreachable_code, "couldn't open the file");
        return 2;
    }
    formals::grammars::CGrammarDeserializer deserializer(iff, formals::grammars::ReadMode::text);
    std::shared_ptr<formals::grammars::CGenerativeGrammar> user_grammar = deserializer.GetGrammar();

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

        for (auto& sym : rule.right_part) {
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

    std::cout << "Representation:\n";
    std::shared_ptr<formals::grammars::CGrammarRepresenter> representer =
            deserializer.GetRepresenter();
    if (representer != nullptr) {
        representer->Represent(user_grammar, std::cout);
    } else {
        formals::errors::ReportError(formals::errors::ErrorType::null_pointer);
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
