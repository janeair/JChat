#ifndef J_OUTPUT_DISPLAY_H
#define J_OUTPUT_DISPLAY_H

#include "common/j_compare_res_t.h"
#include "common/ling/j_ling.h"
#include "common/property/j_msg_property.h"
#include "common/stats/j_msgs_general_stats.h"
#include "common/stats/j_msgs_property_stats.h"
#include "gui/display/j_abstract_display.h"
#include "common/profile/j_profile.h"

enum class j_log_action_t;

using profile_t = QPair<QString, j_msgs_property_stats>;
using profile_t_pointer = QPair<QString, j_msgs_property_stats*>;
using compare_result = QPair<QString, double>;

class j_output_display : public j_abstract_display
{
    Q_OBJECT

public:
    j_output_display(QWidget* parent = nullptr);
    bool get_general_settings() const;
    QList<j_property_id> get_property_settings() const;
    QList<j_compare_res_t> get_compare_settings() const;

signals:

public slots:
    void display_lings(QList<j_ling> lings);
    void display_general_stats(const j_msgs_general_stats &stats);
    void display_property_stats(const j_msgs_property_stats &stats);
    void display_profile(const j_profile* p);
    void display_compare_results(QList<compare_result> list);

};

#endif // J_OUTPUT_DISPLAY_H
