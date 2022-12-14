#pragma once

#include <QMainWindow>

#include "common/ling/j_ling.h"
#include "proc/handlers/j_ling_abstract_handler.h"
#include "gui/display/j_input_display.h"
#include "gui/display/j_output_display.h"
#include "gui/subwindow/j_profile_editor.h"
#include "gui/subwindow/j_compare_analyzer_widget.h"

class j_log_widget;
class j_profile_base;

class jchat_gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit jchat_gui(QWidget *parent = nullptr);
    j_input_display* get_input() { return input; }
    j_output_display* get_output() { return output; }
    j_profile_editor* get_editor() { return editor; }
    j_compare_analyzer_widget* get_analyzer_widget() { return analyzer; }
    j_log_widget* get_log() { return log; }

signals:
    void to_configure_proc(uint32_t msgs, j_handlers ids);
    void to_configure_ling(uint32_t msgs, j_ling_types types);
    void to_configure_comp();

public slots:
    void configure(uint32_t msgs);
    void export_from_log();
    void show_editor(bool show);
    void show_analyzer(bool show);

private:
    j_input_display* input = nullptr;
    j_output_display* output = nullptr;
    action_toolbar* toolbar = nullptr;
    j_profile_editor* editor = nullptr;
    j_compare_analyzer_widget* analyzer = nullptr;
    j_log_widget* log = nullptr;
};
