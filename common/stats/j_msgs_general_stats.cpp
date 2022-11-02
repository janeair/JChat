#include "common/stats/j_msgs_general_stats.h"
#include "common/ling/j_ling.h"

const QString enum_to_string(j_msgs_general_stats_t t)
{
    switch (t)
    {
    case j_msgs_general_stats_t::Messages:
        return QString("Messages");
    case j_msgs_general_stats_t::Lings:
        return QString("Lings");
    case j_msgs_general_stats_t::Words:
        return QString("Words");
    case j_msgs_general_stats_t::Symbols:
        return QString("Symbols");
    case j_msgs_general_stats_t::Signs:
        return QString("Signs");
    case j_msgs_general_stats_t::Numbers:
        return QString("Numbers");
    default:
        return QString();
    }
}

void j_msgs_general_stats::set_data(j_msgs_general_stats_t stat, uint32_t value)
{
    if (stat == j_msgs_general_stats_t::None || stat == j_msgs_general_stats_t::All)
        return;
    uint32_t stat_t = enum_to_uint(stat);
    assert(stat_t < stats.size());
    stats[stat_t] = value;
}

void j_msgs_general_stats::add_data(j_msgs_general_stats_t stat, uint32_t value)
{
    if (stat == j_msgs_general_stats_t::None || stat == j_msgs_general_stats_t::All)
        return;
    uint32_t stat_t = enum_to_uint(stat);
    assert(stat_t < stats.size());
    stats[stat_t] += value;
}

uint32_t j_msgs_general_stats::hash() const
{
    uint32_t value = 0;
    for (uint32_t i : stats)
        value += i * i;
    return value;
}

bool j_msgs_general_stats::join(j_abstract_stats *another, j_stats_join_t type)
{
    if (another->is_property_stats())
        return false;
    j_msgs_general_stats* rv = static_cast<j_msgs_general_stats*>(another);
    uint32_t len = enum_to_uint(j_msgs_general_stats_t::All);
    assert(rv->stats.size() == len);

    for (uint32_t i = 0; i < len; i++)
    {
        switch (type)
        {
        case j_stats_join_t::Extend:
            stats[i] = (stats[i] == 0) ? rv->stats[i] : stats[i];
        break;
        case j_stats_join_t::Deepen:
            stats[i] = (stats[i] == 0) ? 0 : stats[i] + rv->stats[i];
        break;
        case j_stats_join_t::Merge:
            stats[i] += rv->stats[i];
        break;
        }
    }
    return true;
}

void j_msgs_general_stats::clear()
{
    int len = enum_to_uint(j_msgs_general_stats_t::All);
    for (int i = 0; i < len; i++)
        stats[i] = 0;
}

j_msgs_general_stats_t j_msgs_general_stats::from_ling_t(j_ling_type t)
{
    switch (t)
    {
    case j_ling_type::Word:
        return j_msgs_general_stats_t::Words;
    case j_ling_type::Number:
        return j_msgs_general_stats_t::Numbers;
    case j_ling_type::Sign:
        return j_msgs_general_stats_t::Signs;
    case j_ling_type::Symbol:
        return j_msgs_general_stats_t::Symbols;
    case j_ling_type::Separator:
    case j_ling_type::ND:
    default:
        return j_msgs_general_stats_t::None;
    }
}

int32_t enum_to_uint(j_msgs_general_stats_t t)
{
    switch (t)
    {
    case j_msgs_general_stats_t::Messages:
        return 0;
    case j_msgs_general_stats_t::Lings:
        return 1;
    case j_msgs_general_stats_t::Words:
        return 2;
    case j_msgs_general_stats_t::Symbols:
        return 3;
    case j_msgs_general_stats_t::Signs:
        return 4;
    case j_msgs_general_stats_t::Numbers:
        return 5;
    case j_msgs_general_stats_t::All:
        return 6;
    default:
        return -1;
    }
}

j_msgs_general_stats_t uint_to_general_enum(uint32_t t)
{
    switch (t)
    {
    case 0:
        return j_msgs_general_stats_t::Messages;
    case 1:
        return j_msgs_general_stats_t::Lings;
    case 2:
        return j_msgs_general_stats_t::Words;
    case 3:
        return j_msgs_general_stats_t::Symbols;
    case 4:
        return j_msgs_general_stats_t::Signs;
    case 5:
        return j_msgs_general_stats_t::Numbers;
    default:
        return j_msgs_general_stats_t::None;
    }
}
