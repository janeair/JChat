#include "gui/display/j_input_display.h"

#include "gui/display/j_display_type.h"
#include "gui/common/j_action_toolbar.h"

#include <QTextEdit>

j_input_display::j_input_display(QWidget* parent)
    : j_abstract_display(
          j_display_type::input,
          parent
          )
{
    /// configure toolbar
    toolbar()->add_action<settings_widget>
            (icon(j_toolbar_action_t::A_SETTINGS), "Show/hide settings", settings(), &settings_widget::setVisible);
    toolbar()->add_action<j_input_display>
            (icon(j_toolbar_action_t::A_IMPORT), "Import from text file", this, &j_input_display::import_to_field);
    toolbar()->add_action<j_input_display, j_input_display>
            (icon(j_toolbar_action_t::A_SELECT), "Process text", this, &j_input_display::process_input, this, &j_input_display::field_text_changed, false);
    toolbar()->add_action<QTextEdit, j_input_display>
            (icon(j_toolbar_action_t::A_DELETE), "Clear field", field(), &QTextEdit::clear, this, &j_input_display::field_text_changed, false);

    /// configure field
    field()->setAlignment(Qt::AlignLeft);
}

j_ling_types j_input_display::get_ling_settings() const
{
    return j_ling_type::All;
}

j_handlers j_input_display::get_proc_settings() const
{
    return j_handler_id::AllHandlers;
}

bool j_input_display::get_comp_settings() const
{
    return true;
}

void j_input_display::process_input()
{
    QStringList msg_list = field()->toPlainText().split('\n', Qt::SkipEmptyParts);
    if (msg_list.count() > 0)
    {
        Q_EMIT to_configure(msg_list.size());
        foreach (QString msg, msg_list)
            Q_EMIT to_analyse(msg);
    }
}
