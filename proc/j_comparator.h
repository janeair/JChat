#ifndef J_COMPARATOR_H
#define J_COMPARATOR_H

#include <QObject>

#include "common/j_msgs_property_stats.h"

class j_profile_loader;

using COMPARE_RES = QPair<QString, double>;

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
    explicit j_comparator(j_profile_loader* loader, QObject *parent = nullptr);
    void set_loader(j_profile_loader* loader) { base = loader; }

public slots:
    void compare_stats_with_base(j_msgs_property_stats stats);
    void configure_settings();

signals:
    void results_to_gui(QList<COMPARE_RES> res);

private:
    j_comparator_state_t state = j_comparator_state_t::Not_Ready;
    j_profile_loader* base = nullptr;

    double compare_stats(j_msgs_property_stats first, j_msgs_property_stats second);
};

#endif // J_COMPARATOR_H
