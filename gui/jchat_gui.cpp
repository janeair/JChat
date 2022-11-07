#include "jchat_gui.h"

#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QDockWidget>

#include "gui/common/j_action_toolbar.h"
#include "gui/log/jchat_log.h"
#include "gui/subwindow/text_file_io_dialog.h"

jchat_gui::jchat_gui(QWidget *parent) : QMainWindow(parent)
{
    input = new j_input_display();
    output = new j_output_display();
    toolbar = new action_toolbar("Actions", this);
    log = new j_log_widget(this);
    editor = new j_profile_editor(this);
    analyzer = new j_compare_analyzer_widget(this);

    toolbar->add_action<jchat_gui>
            (icon(j_toolbar_action_t::A_EDIT_PROFILE), "Profile editor", this, &jchat_gui::show_editor);
    toolbar->add_action<jchat_gui>
            (icon(j_toolbar_action_t::A_ADD_PROFILE), "Compare analyzer", this, &jchat_gui::show_analyzer);
    toolbar->add_action<jchat_gui, j_log_widget>
            (icon(j_toolbar_action_t::A_EXPORT), "Export history", this, &jchat_gui::export_from_log, log, &j_log_widget::log_text_changed, false);
    toolbar->add_action<j_log_widget, j_log_widget>
            (icon(j_toolbar_action_t::A_DELETE), "Clear history", log, &j_log_widget::clear, log, &j_log_widget::log_text_changed, false);

    connect(input, &j_input_display::to_configure, this, &jchat_gui::configure);

    connect(output, &j_output_display::log_this, log, &j_log_widget::log_message);
    connect(input, &j_input_display::log_this, log, &j_log_widget::log_message);
    connect(editor->get_data_model(), &j_profile_editor_table_model::log_this, log, &j_log_widget::log_message);

    connect(editor, &j_profile_editor::profile_to_display, output, &j_output_display::display_profile);

    setWindowIcon(QIcon(":/icons/resources/app_icon.ico"));

    auto central_scene = new QMainWindow();
    central_scene->addDockWidget(Qt::LeftDockWidgetArea, input);
    central_scene->addDockWidget(Qt::RightDockWidgetArea, output);
    setCentralWidget(central_scene);
    addDockWidget(Qt::BottomDockWidgetArea, log);
    addToolBar(Qt::LeftToolBarArea, toolbar);
}

void jchat_gui::configure(uint32_t msgs)
{
    get_output()->field()->clear();

    Q_EMIT to_configure_ling(msgs, input->get_ling_settings());
    Q_EMIT to_configure_proc(msgs, input->get_proc_settings());
    if (input->get_comp_settings())
        Q_EMIT to_configure_comp();
}

void jchat_gui::export_from_log()
{
    if (io_dialog::save_text_content(this, log->log_widget()->toPlainText()))
        log->log_message(j_log_action_t::EXPORT_DATA, log->windowTitle().toLower());
}

void jchat_gui::show_editor()
{
    if (editor && editor->isHidden())
        editor->show();
}

void jchat_gui::show_analyzer()
{
    if (analyzer && analyzer->isHidden())
        analyzer->show();
}
