#include "common/stats/j_msgs_property_stats.h"
#include "common/property/j_msg_property.h"

j_msgs_property_stats::j_msgs_property_stats()
{
}

j_msgs_property_stats::j_msgs_property_stats(const j_msgs_property_stats &another)
{
    foreach(auto prop, another.list())
        append(prop);
}

j_msgs_property_stats::~j_msgs_property_stats()
{
}

bool j_msgs_property_stats::append(j_abstract_property* property)
{
    property_list.append(property);
    return true;
}

bool j_msgs_property_stats::is_clear() const
{
    return (property_list.count() <= 0);
}

j_abstract_property *j_msgs_property_stats::at(uint t)
{
    return (t < property_list.count()) ? property_list[t] : nullptr;
}

uint32_t j_msgs_property_stats::hash() const
{
    uint32_t value = 0;
    auto t_list = list();
    foreach (j_abstract_property* t, t_list)
        value += t->weight() * t->weight();
    return value;
}

bool j_msgs_property_stats::join(j_abstract_stats* another, j_stats_join_t type)
{
    if (!another->is_property_stats())
        return false;
    auto prop_list = static_cast<j_msgs_property_stats*>(another)->list();

    uint len = property_list.size();
    foreach (j_abstract_property* prop, prop_list)
    {
        bool joined = false;
        for (uint i = 0; i < len; ++i)
        {
            joined = (type == j_stats_join_t::Extend) ?
                     j_abstract_property::can_be_merged(at(i), prop) : at(i)->join(prop);
            if (joined)
                break;
        }
        if (!joined && type != j_stats_join_t::Deepen)
        {
            append(std::move(prop));
        }
    }
    return true;
}

void j_msgs_property_stats::clear()
{
   property_list.clear();
}
