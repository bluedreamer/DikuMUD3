#pragma once

#include "essential.h"
#include "namelist.h"

class unit_dil_affected_type
{
    /// @todo This is completely unused anywhere - but it must have been used for something
    ///  once so I am leaving it here all private and uncreatable.
public:
    unit_dil_affected_type() = delete;

private:
    uint16_t beat{0};
    uint16_t duration{0};
    uint16_t transfer{0};
    cNamelist data;
    char *apply{nullptr};  ///< Apply DIL
    char *remove{nullptr}; ///< Remove DIL
    unit_dil_affected_type *next{nullptr};
};
