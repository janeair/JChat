#ifndef J_STATS_T_H
#define J_STATS_T_H

#include <QString>
#include <QColor>

enum class j_stats_t
{
    general,
    property,
    compare,

    COUNT
};

const QString enum_to_string(j_stats_t t);
const QString enum_to_full_string(j_stats_t t);
QColor enum_to_default_color(j_stats_t t);

#endif // J_STATS_T_H
