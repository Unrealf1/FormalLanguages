//
// Created by fedor on 3/16/19.
//

#ifndef FORMALLANGUAGES_ERRORHELPER_H
#define FORMALLANGUAGES_ERRORHELPER_H

#include <iostream>
#include <string>

namespace formals { namespace errors {
    enum class ErrorType {
        not_implemented, wrong_text_format, unreachable_code, null_pointer
    };

    void ReportError(ErrorType error, const std::string& info = "Error");
}}

#endif //FORMALLANGUAGES_ERRORHELPER_H
