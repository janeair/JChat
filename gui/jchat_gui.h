#pragma once

#include <QMainWindow>

#include "common/j_ling.h"
#include "common/j_msgs_general_stats.h"
#include "common/j_msgs_property_stats.h"
#include "proc/handlers/j_ling_abstract_handler.h"
#include "common/j_settings.h"
#include "gui/display/j_input_display.h"
#include "gui/display/j_output_display.h"

class j_log_widget;

class jchat_gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit jchat_gui(QWidget *parent = nullptr);
    j_input_display* get_input() { return input; }
    j_output_display* get_output() { return output; }

signals:
    void to_analyse(const QString& msg);
    void to_configure_proc(uint32_t msgs, j_handlers ids);
    void to_configure_ling(uint32_t msgs, j_ling_types types);
    void to_configure_comp();

public slots:
    void configure(uint32_t msgs, j_settings st);

private:
    j_input_display* input = nullptr;
    j_output_display* output = nullptr;
    j_action_toolbar* toolbar = nullptr;
    j_log_widget* log = nullptr;
};
