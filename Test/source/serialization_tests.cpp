//
// Created by fedor on 3/18/19.
//

#include <fstream>
#include <memory>
#include <cinttypes>
#include <cstdarg>
#include <unordered_set>
#include <dirent.h>
#include "test_main.hpp"
#include "gtest/gtest.h"
#include "Grammar/CGenerativeGrammar.hpp"
#include "Grammar/Serialization/CGrammarDeserializer.hpp"
#include "Grammar/Serialization/CGrammarRepresenter.h"
#include "ErrorHelper.h"


extern std::string path_to_test;
using ErrorType = formals::errors::ErrorType;
const std::string to_samples = "Samples/Grammars/Text/";
const std::string to_answers = "Answers/Grammars/Deserialization/";

void ReadDeserializationAnswers(
        std::istream& is,
        size_t& terminals,
        size_t& non_terminals,
        size_t& starting,
        size_t& rules) {
    is >> terminals >> non_terminals >> starting >> rules;
}

TEST(DeserializationTests, CBS_1)
{
    const std::string error_info = "Deserialization CBS_1 test";
    const std::string test_file_path = path_to_test + "Samples/Grammars/Text/CBS_1";
    std::ifstream iff (test_file_path);
    if (iff.fail()) {
        formals::errors::ReportError(ErrorType::cant_open_file, test_file_path);
        ASSERT_TRUE(false);
    }
    formals::grammars::CGrammarDeserializer deserializer(iff, formals::grammars::ReadMode::text);
    std::shared_ptr<formals::grammars::CGenerativeGrammar> user_grammar = deserializer.GetGrammar();
    if (user_grammar == nullptr) {
        formals::errors::ReportError(ErrorType::null_pointer, error_info);
        ASSERT_TRUE(false);
    }

    std::unordered_set<formals::grammars::ruleSymbolValyeType> terminals;
    std::unordered_set<formals::grammars::ruleSymbolValyeType> non_terminals;
    std::unordered_set<formals::grammars::ruleSymbolValyeType> starting_non_terminals;

    const std::string answer_file_path = path_to_test + "Answers/Grammars/Deserialization/CBS_1";
    std::ifstream answer (answer_file_path);
    if (answer.fail()) {
        formals::errors::ReportError(ErrorType::cant_open_file, answer_file_path);
        ASSERT_TRUE(false);
    }

    size_t terminals_count_answer = 0;
    size_t non_terminals_count_answer = 0;
    size_t starting_non_terminals_count_answer = 0;
    size_t rule_count_answer = 0;
    ReadDeserializationAnswers(answer, terminals_count_answer,
            non_terminals_count_answer, starting_non_terminals_count_answer,
            rule_count_answer);

    ASSERT_EQ(rule_count_answer, user_grammar->Size());
    for (auto& rule : *user_grammar) {
        for (auto& sym : rule.left_part) {
            std::cout << sym.value;
            if (!sym.is_terminal) {
                non_terminals.insert(sym.value);
                std::cout << '*';
                if (sym.is_starting) {
                    starting_non_terminals.insert(sym.value);
                    std::cout << 'S';
                }
            } else {
                terminals.insert(sym.value);
            }
            std::cout << ' ';
        }

        std::cout << "-> ";

        for (auto& sym : rule.right_part) {
            std::cout << sym.value;
            if (!sym.is_terminal) {
                non_terminals.insert(sym.value);
                std::cout << '*';
                if (sym.is_starting) {
                    starting_non_terminals.insert(sym.value);
                    std::cout << 'S';
                }
            } else {
                terminals.insert(sym.value);
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    ASSERT_EQ(terminals_count_answer, terminals.size());
    ASSERT_EQ(non_terminals_count_answer, non_terminals.size());
    ASSERT_EQ(starting_non_terminals_count_answer, starting_non_terminals.size());
}

TEST(DeserializationTests, test_samples) {
    DIR* dir = opendir((path_to_test + to_samples).c_str());
    dirent* entry;
    while ((entry = readdir(dir))) {
        if (entry->d_type != DT_REG) {
            continue;
        }
        std::string file_name = entry->d_name;
        const std::string error_info = "Deserialization " + file_name;
        const std::string test_file_path = path_to_test + to_samples + file_name;
        std::ifstream iff (test_file_path);
        if (iff.fail()) {
            formals::errors::ReportError(ErrorType::cant_open_file, test_file_path);
            ASSERT_TRUE(false);
        }
        formals::grammars::CGrammarDeserializer deserializer(iff, formals::grammars::ReadMode::text);
        std::shared_ptr<formals::grammars::CGenerativeGrammar> user_grammar = deserializer.GetGrammar();
        if (user_grammar == nullptr) {
            formals::errors::ReportError(ErrorType::null_pointer, error_info);
            ASSERT_TRUE(false);
        }
        iff.close();
        std::unordered_set<formals::grammars::ruleSymbolValyeType> terminals;
        std::unordered_set<formals::grammars::ruleSymbolValyeType> non_terminals;
        std::unordered_set<formals::grammars::ruleSymbolValyeType> starting_non_terminals;

        const std::string answer_file_path = path_to_test + to_answers + file_name;
        std::ifstream answer (answer_file_path);
        if (answer.fail()) {
            formals::errors::ReportError(ErrorType::cant_open_file, answer_file_path);
            ASSERT_TRUE(false);
        }

        size_t terminals_count_answer = 0;
        size_t non_terminals_count_answer = 0;
        size_t starting_non_terminals_count_answer = 0;
        size_t rule_count_answer = 0;
        ReadDeserializationAnswers(answer, terminals_count_answer,
                                   non_terminals_count_answer, starting_non_terminals_count_answer,
                                   rule_count_answer);
        answer.close();
        ASSERT_EQ(rule_count_answer, user_grammar->Size());
        for (auto& rule : *user_grammar) {
            for (auto& sym : rule.left_part) {
                if (!sym.is_terminal) {
                    non_terminals.insert(sym.value);
                    if (sym.is_starting) {
                        starting_non_terminals.insert(sym.value);
                    }
                } else {
                    terminals.insert(sym.value);
                }
            }

            for (auto& sym : rule.right_part) {
                if (!sym.is_terminal) {
                    non_terminals.insert(sym.value);
                    if (sym.is_starting) {
                        starting_non_terminals.insert(sym.value);
                    }
                } else {
                    terminals.insert(sym.value);
                }
            }
        }
        ASSERT_EQ(terminals_count_answer, terminals.size());
        ASSERT_EQ(non_terminals_count_answer, non_terminals.size());
        ASSERT_EQ(starting_non_terminals_count_answer, starting_non_terminals.size());
    }
}