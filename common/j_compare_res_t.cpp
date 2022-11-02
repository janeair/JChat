#include "j_compare_res_t.h"

#include <QString>
#include <QColor>

const QString enum_to_string(j_compare_res_t t)
{
    switch (t)
    {
    case j_compare_res_t::TopMatch:
        return QString("Top Match");
    case j_compare_res_t::MiddleMatch:
        return QString("Mid Match");
    case j_compare_res_t::LowMatch:
        return QString("Low Match");
    default:
        return QString();
    }
}

const QColor enum_to_default_color(j_compare_res_t t)
{
    switch (t)
    {
    case j_compare_res_t::TopMatch:
        return Qt::darkGreen;
    case j_compare_res_t::MiddleMatch:
        return Qt::darkBlue;
    case j_compare_res_t::LowMatch:
        return Qt::darkRed;
    default:
        return QColor();
    }
}

j_compare_res_t compare_res_t_from_value(double value)
{
    if (value > 0.8)
        return j_compare_res_t::TopMatch;
    else if (value > 0.5)
        return j_compare_res_t::MiddleMatch;
    else
        return j_compare_res_t::LowMatch;
}
