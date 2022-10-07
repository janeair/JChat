#include "j_ling_abstract_handler.h"

j_ling_abstract_handler::j_ling_abstract_handler(j_handler_id type, j_langs proc_langs, j_ling_types proc_types, QObject *parent)
    : QObject(parent), handler_type(type), languages(proc_langs), ling_types(proc_types)
{

}

QString enum_to_string(j_handler_id t)
{
    switch (t)
    {
    case j_handler_id::GWHandler:
        return QString("GWHandler");
    default:
        return QString();
    }
}
