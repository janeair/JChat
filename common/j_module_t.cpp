#include "common/j_module_t.h"

#include <QString>

QString enum_to_string(j_module_t t)
{
    switch (t)
    {
    case j_module_t::Linguist:
        return QString("Linguist");
    case j_module_t::Processor:
        return QString("Processor");
    case j_module_t::Comparator:
        return QString("Comparator");
    default:
        return QString();
    }
}
