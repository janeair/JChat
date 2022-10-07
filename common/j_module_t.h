#ifndef J_MODULE_T_H
#define J_MODULE_T_H

#include <QFlags>

class QString;

enum class j_module_t
{
    None = 0x0,
    Linguist = 0x1,
    Processor = 0x2,
    Comparator = 0x4,
    All = 0x7,
};

QString enum_to_string(j_module_t t);

Q_DECLARE_FLAGS(j_modules_t, j_module_t);
Q_DECLARE_OPERATORS_FOR_FLAGS(j_modules_t);

#endif // J_MODULE_T_H
