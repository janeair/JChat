#include "common/j_ling.h"

const QString enum_to_string(j_ling_type t)
{
    switch (t)
    {
    case j_ling_type::Word:
        return QString("Word");
    case j_ling_type::Symbol:
        return QString("Symbol");
    case j_ling_type::Sign:
        return QString("Sign");
    case j_ling_type::Number:
        return QString("Number");
    case j_ling_type::Separator:
        return QString("Separator");
    case j_ling_type::ND:
        return QString("N/D");
    default:
        return QString();
    }
}

const QString enum_to_string(j_lang t)
{
    switch (t)
    {
    case j_lang::Rus:
        return QString("Russian");
    case j_lang::Eng:
        return QString("English");
    case j_lang::ND:
        return QString("N/D");
    }
    return QString();
}

j_ling_char_t j_ling::can_be_multiple_char(j_ling_type t)
{
    switch(t)
    {
    case j_ling_type::Word:
    case j_ling_type::Number:
        /// these types are always multi-char
        return j_ling_char_t::Multiple;
    case j_ling_type::Sign:
    case j_ling_type::Separator:
        /// these types can be multi-char when the same chars
        return j_ling_char_t::MultipleIfSame;
    case j_ling_type::Symbol:
    case j_ling_type::ND:
        /// these types are always single-char
        return j_ling_char_t::Single;
    default:
        return j_ling_char_t::Single;
    }
}
