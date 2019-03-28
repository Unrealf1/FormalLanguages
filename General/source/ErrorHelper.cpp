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
                std::cout << "Reached unreachable code! " << info << std::endl;
                break;
            }
            case ErrorType::null_pointer: {
                std::cout << info << ": Got null pointer" << std::endl;
                break;
            }
            case ErrorType::cant_open_file: {
                std::cout << info << ": Can't open file" << std::endl;
                break;
            }
            case ErrorType::exception: {
                std::cout << "Caught exception:" << info << std::endl;
                break;
            }
            case ErrorType::general: {
                std::cout << "Error: " << info << std::endl;
                break;
            }
        }
    }
}}