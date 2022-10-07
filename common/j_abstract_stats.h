#pragma once

#include <stdint.h>

enum class j_stats_join_t
{
    Extend,
    Deepen,
    Merge
};

class j_abstract_stats
{
public:
    virtual bool is_property_stats() const = 0;
    virtual uint32_t hash() const = 0;
    virtual bool join(j_abstract_stats* another, j_stats_join_t type) = 0;
    virtual void clear() = 0;

};
