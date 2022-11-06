#pragma once

#include <QString>
#include <QColor>

enum class j_ling_type
{
    None = 0x0,
    Word = 0x1,
    Symbol = 0x2,
    Sign = 0x4,
    Number = 0x8,
    Separator = 0x10,
    ND = 0x20,
    All = 0x3F,
};

const QString enum_to_string(j_ling_type t);
int enum_to_int(j_ling_type t);
QColor enum_to_default_color(j_ling_type t);
j_ling_type ling_type_from_int (int n);

enum class j_lang
{
    Rus = 0x1,
    Eng = 0x2,
    ND = 0x4,
};

const QString enum_to_string(j_lang t);

Q_DECLARE_FLAGS(j_ling_types, j_ling_type);
Q_DECLARE_FLAGS(j_langs, j_lang);

enum class j_ling_char_t
{
    Single,
    Multiple,
    MultipleIfSame,
};

class j_ling
{
public:
    j_ling (j_ling_type _type, j_lang _lang, const QString _str) : type(_type), lang(_lang), str(_str) {};
    j_ling_type type;
    j_lang lang;
    QString str;

    static j_ling_char_t can_be_multiple_char(j_ling_type t);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(j_ling_types);
Q_DECLARE_OPERATORS_FOR_FLAGS(j_langs);
