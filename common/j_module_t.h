#ifndef J_MODULE_T_H
#define J_MODULE_T_H

#include <QFlags>

class QString;

enum class j_module_t
{
    Linguist,
    Processor,
    Comparator,

    COUNT,
};

QString enum_to_string(j_module_t t);

#endif // J_MODULE_T_H
