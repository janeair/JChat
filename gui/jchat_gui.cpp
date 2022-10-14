#include "jchat_gui.h"

#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QDockWidget>

#include <QDebug>

#include "gui/common/j_action_toolbar.h"
#include "gui/log/jchat_log.h"
#include "gui/display/settings/j_settings.h"

jchat_gui::jchat_gui(QWidget *parent) : QMainWindow(parent)
{
    input = new j_input_display();
    output = new j_output_display();
    toolbar = new action_toolbar("Actions", this);
    log = new j_log_widget(this);

    //toolbar->add_action(j_toolbar_action_t::A_EDIT_PROFILE, "Edit Profiles");
    //toolbar->add_action(j_toolbar_action_t::A_EXPORT, "Export history", false);
    toolbar->add_action<j_log_widget, j_log_widget>
            (icon(j_toolbar_action_t::A_DELETE), "Clear history", log, &j_log_widget::clear, log, &j_log_widget::log_text_changed, false);

    connect(input, &j_input_display::to_configure, this, &jchat_gui::configure);
    connect(output, &j_output_display::log_this, log, &j_log_widget::log_message);

    setWindowIcon(QIcon(":/icons/resources/app_icon.ico"));

    QMainWindow* central_scene = new QMainWindow();
    central_scene->addDockWidget(Qt::LeftDockWidgetArea, input);
    central_scene->addDockWidget(Qt::RightDockWidgetArea, output);
    setCentralWidget(central_scene);
    addDockWidget(Qt::BottomDockWidgetArea, log);
    addToolBar(Qt::LeftToolBarArea, toolbar);
}

void jchat_gui::configure(uint32_t msgs, j_settings st)
{
    get_output()->field()->clear();
    j_modules_t modules = static_cast<j_modules_t>(st.get_settings(j_settings_t::Modules));
    if (modules.testFlag(j_module_t::Linguist))
    {
        emit to_configure_ling(msgs, static_cast<j_ling_types>(st.get_settings(j_settings_t::Lings)));
        if (modules.testFlag(j_module_t::Processor))
        {
            emit to_configure_proc(msgs, static_cast<j_handlers>(st.get_settings(j_settings_t::Handlers)));
            if (modules.testFlag(j_module_t::Comparator))
                emit to_configure_comp();
        }
    }
}
