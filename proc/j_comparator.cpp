#include "j_comparator.h"

#include "common/property/j_msg_property.h"
#include "common/profile/j_profile.h"

#include <QDebug>

j_comparator::j_comparator(QObject *parent) : QObject(parent) {}

j_comparator::j_comparator(j_profile_base *p_base, QObject *parent) : QObject(parent), base(p_base) {}

void j_comparator::compare_stats_with_base(j_msgs_property_stats stats)
{
    if (state == j_comparator_state_t::Is_Ready)
        state = j_comparator_state_t::Is_Busy;
    else
        return;

    QList<compare_res> res_list;
    const auto profiles = base->get_profiles();
    foreach (auto p, profiles)
    {
        if (!p)
            continue;
        j_msgs_property_stats* p_data = p->get_data();
        if (p_data && p->is_valid())
        {
            auto res = compare_stats(stats, *p_data);
            res_list.append(compare_res(p->get_name(), res));
        }
    }
    if (res_list.count() > 0)
        emit results_to_gui(std::move(res_list));

    state = j_comparator_state_t::Not_Ready;
}

void j_comparator::configure_settings()
{
    Q_ASSERT (state == j_comparator_state_t::Not_Ready);
    state = j_comparator_state_t::Is_Ready;
    qDebug() << "comparator: configure settings";
}

double j_comparator::compare_stats(const j_msgs_property_stats &first, const j_msgs_property_stats &second)
{
    double res = 0.;
    int res_value = 0;
    /// value for each property in future
    const int value = 1;
    auto list1 = first.list();
    auto list2 = second.list();
    foreach (auto prop, list1)
    {
        auto match = std::find_if(list2.cbegin(), list2.cend(),
                                  [prop](j_abstract_property* i) { return (prop->id_enum() == i->id_enum()); });
        if (match != list2.cend())
        {
            res += value * prop->correlation(*match);
            res_value += value;
        }
    }
    return (res_value == 0) ? 0 : res / res_value;
}
