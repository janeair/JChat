#include "j_stats_t.h"

const QString enum_to_string(j_stats_t t)
{
    switch (t)
    {
    case j_stats_t::general:
        return QString("General");
    case j_stats_t::property:
        return QString("Property");
    case j_stats_t::compare:
        return QString("Compare");
    default:
        return QString();
    }
}

QColor enum_to_default_color(j_stats_t t)
{
    switch (t)
    {
    case j_stats_t::general:
        return Qt::black;
    case j_stats_t::property:
        return Qt::darkBlue;
    case j_stats_t::compare:
        return Qt::darkGreen;
    default:
        return QColor();
    }
}
