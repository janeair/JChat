#ifndef J_OUTPUT_DISPLAY_H
#define J_OUTPUT_DISPLAY_H

#include "common/ling/j_ling.h"
#include "common/stats/j_msgs_general_stats.h"
#include "common/stats/j_msgs_property_stats.h"
#include "gui/display/j_abstract_display.h"

enum class j_log_action_t;

using profile_t = QPair<QString, j_msgs_property_stats>;
using profile_t_pointer = QPair<QString, j_msgs_property_stats*>;
using compare_result = QPair<QString, double>;

class j_output_display : public j_abstract_display
{
    Q_OBJECT

public:
    j_output_display(QWidget* parent = nullptr);

signals:

public slots:
    void display_lings(QList<j_ling> lings);
    void display_general_stats(j_msgs_general_stats stats);
    void display_property_stats(j_msgs_property_stats stats);
    void display_profile(profile_t_pointer profile);
    void display_compare_results(QList<compare_result> list);
    void save_property_stats(j_msgs_property_stats stats);

private:
    j_msgs_property_stats current_stats;
};

#endif // J_OUTPUT_DISPLAY_H
