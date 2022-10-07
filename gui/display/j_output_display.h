#ifndef J_OUTPUT_DISPLAY_H
#define J_OUTPUT_DISPLAY_H

#include "common/j_ling.h"
#include "common/j_msgs_general_stats.h"
#include "common/j_msgs_property_stats.h"
#include "common/j_settings.h"
#include "gui/display/j_abstract_display.h"
#include "gui/display/output/j_profile_dialog.h"

enum class j_log_action_t;

using PROFILE = QPair<QString, j_msgs_property_stats>;
using PROFILE_P = QPair<QString, j_msgs_property_stats*>;
using COMPARE_RES = QPair<QString, double>;

class j_output_display : public j_abstract_display
{
    Q_OBJECT

public:
    j_output_display(QWidget* parent = nullptr);

signals:
    void new_profile(PROFILE profile);
    void get_profile_data(QString name);
    void log_this(j_log_action_t t, QString decr);

public slots:
    void display_lings(QList<j_ling> lings);
    void display_general_stats(j_msgs_general_stats stats);
    void display_property_stats(j_msgs_property_stats stats);
    void display_profile(PROFILE_P profile);
    void display_compare_results(QList<COMPARE_RES> list);
    void save_property_stats(j_msgs_property_stats stats);

    void on_change_profiles(QStringList profiles);
    void save_to_profile_dialog();
    void open_profile_dialog();
    void on_selected_profile(j_profile_dialog_action action, QString name);

private:
    QStringList loaded_profiles;
    j_msgs_property_stats current_stats;
    j_profile_dialog* dlg = nullptr;
};

#endif // J_OUTPUT_DISPLAY_H
