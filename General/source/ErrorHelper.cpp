//
// Created by fedor on 3/16/19.
//

#include "ErrorHelper.h"

namespace formals { namespace  errors {
    void ReportError(ErrorType error, const std::string& info) {
        switch (error) {
            case ErrorType::not_implemented: {
                std::cerr << info << ": This is not implemented yet" << std::endl;
                break;
            }
            case ErrorType::wrong_text_format: {
                std::cout << info << ": Wrong text format" << std::endl;
                break;
            }
            case ErrorType::unreachable_code: {
                std::cout << info << ": Reached unreachable code!" << std::endl;
            }
        }
    }
}}