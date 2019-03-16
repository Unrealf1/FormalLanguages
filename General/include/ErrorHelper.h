//
// Created by fedor on 3/16/19.
//

#ifndef FORMALLANGUAGES_ERRORHELPER_H
#define FORMALLANGUAGES_ERRORHELPER_H

#include <iostream>

namespace formals { namespace errors {
    enum ErrorType {
        not_implemented, wrong_text_format, unreachable_code
    };

    void ReportError(ErrorType error);
}}

#endif //FORMALLANGUAGES_ERRORHELPER_H
