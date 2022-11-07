#ifndef J_COMPARATOR_H
#define J_COMPARATOR_H

#include <QObject>

#include "common/stats/j_msgs_property_stats.h"
#include "import/single_weight_data.h"

class j_profile_base;

using compare_res = QPair<QString, double>;

enum class j_comparator_state_t
{
    Not_Ready,
    Is_Ready,
    Is_Busy,

    COUNT
};

class j_comparator : public QObject
{
    Q_OBJECT

public:
    explicit j_comparator(QObject *parent = nullptr);
    single_weight_data* get_weights() { return prop_weights.get(); }

public slots:
    void set_profile_base(j_profile_base* p_base) { base = p_base; }
    void compare_stats_with_base(j_msgs_property_stats stats);
    void configure_settings();

signals:
    void results_to_gui(QList<compare_res> res);

private:
    j_comparator_state_t state = j_comparator_state_t::Not_Ready;
    j_profile_base* base = nullptr;
    std::unique_ptr<single_weight_data> prop_weights = nullptr;

    double compare_stats(const j_msgs_property_stats &first, const j_msgs_property_stats &second);
};

#endif // J_COMPARATOR_H
