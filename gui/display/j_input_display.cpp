#include "gui/display/j_input_display.h"

#include "gui/display/j_action_toolbar.h"

#include <QTextEdit>

j_input_display::j_input_display(QWidget* parent)
    : j_abstract_display(
          QString("Input"),
          j_settings(j_settings_t::Lings | j_settings_t::Modules | j_settings_t::Handlers),
          parent
          )
{
    /// configure toolbar
    toolbar()->add_action(j_toolbar_action_t::A_CHECKALL, "Select all settings");
    toolbar()->add_action(j_toolbar_action_t::A_PLAY, "Process text");
    toolbar()->add_action(j_toolbar_action_t::A_CLEAR, "Clear field");

    connect(toolbar(), &j_action_toolbar::to_play, this, &j_input_display::process_input);
    field()->setAlignment(Qt::AlignLeft);
}

void j_input_display::process_input()
{
    QStringList msg_list = field()->toPlainText().split('\n', Qt::SkipEmptyParts);
    if (msg_list.count() > 0)
    {
        emit to_configure(msg_list.size(), settings_widget()->settings());
        foreach (QString msg, msg_list)
            emit to_analyse(msg);
    }
}
