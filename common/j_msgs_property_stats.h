#pragma once

#include <QList>
#include "common/j_abstract_stats.h"

class j_abstract_property;

class j_msgs_property_stats : public j_abstract_stats
{
public:
    j_msgs_property_stats();
    j_msgs_property_stats(const j_msgs_property_stats &another);
    ~j_msgs_property_stats() = default;

    const QList<j_abstract_property*> list() const { return *property_list; };
    bool append(j_abstract_property* property);
    bool is_clear() const;
    j_abstract_property* at(uint t);
    virtual bool is_property_stats() const override { return true; };
    virtual uint32_t hash() const override;
    virtual bool join(j_abstract_stats* another, j_stats_join_t type) override;
    virtual void clear() override;

private:
    QList<j_abstract_property*> *property_list = nullptr;
};
