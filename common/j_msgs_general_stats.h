#pragma once

#include <QString>
#include "common/j_abstract_stats.h"

enum class j_msgs_general_stats_t
{
    None = 0x0,
    Messages = 0x1,
    Lings = 0x2,
    Words = 0x4,
    Symbols = 0x8,
    Signs = 0x10,
    Numbers = 0x20,
    All = 0x3F,
};

const QString enum_to_string(j_msgs_general_stats_t t);
uint32_t enum_to_uint(j_msgs_general_stats_t t);
j_msgs_general_stats_t uint_to_general_enum(uint32_t t);

Q_DECLARE_FLAGS(j_msgs_general_stats_types, j_msgs_general_stats_t);
Q_DECLARE_OPERATORS_FOR_FLAGS(j_msgs_general_stats_types);

enum class j_ling_type;

class j_msgs_general_stats : public j_abstract_stats
{
public:
    j_msgs_general_stats()
    {
        int len = enum_to_uint(j_msgs_general_stats_t::All);
        for (int i = 0; i < len; i++)
            stats.push_back(0);
    }
    ~j_msgs_general_stats() = default;
    std::vector<uint32_t> statistics() const { return stats; }
    void set_data(j_msgs_general_stats_t stat, uint32_t value);
    void add_data(j_msgs_general_stats_t stat, uint32_t value);
    virtual bool is_property_stats() const override { return false; };
    virtual uint32_t hash() const override;
    virtual bool join(j_abstract_stats* another, j_stats_join_t type) override;
    virtual void clear() override;

    static j_msgs_general_stats_t from_ling_t(j_ling_type t);

private:
    std::vector<uint32_t> stats = {};
};
