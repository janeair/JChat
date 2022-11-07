#include "gui/display/j_input_display.h"

#include "gui/display/j_display_type.h"
#include "gui/common/j_action_toolbar.h"
#include "common/j_module_t.h"

#include <QTextEdit>

j_input_display::j_input_display(QWidget* parent)
    : j_abstract_display(
          j_display_type::input,
          parent
          )
{
    /// configure toolbar
    toolbar()->add_action<tree_settings_widget>
            (icon(j_toolbar_action_t::A_SETTINGS), "Show/hide settings", settings(), &tree_settings_widget::setVisible);
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
    j_ling_types res = j_ling_type::None;
    int section = static_cast<int>(j_module_t::Linguist);
    const auto model = settings()->get_model();
    const auto top_item = model->top_level_item(section);
    bool is_checked = top_item->is_checked();
    if (!is_checked)
        return res;
    auto list = top_item->get_childs();
    foreach (auto item, list)
        if (item->is_checked())
            res |= ling_type_from_int(item->row());
    return res;
}

j_handlers j_input_display::get_proc_settings() const
{
    j_handlers res = j_handler_id::NoHandler;
    int section = static_cast<int>(j_module_t::Processor);
    const auto model = settings()->get_model();
    const auto top_item = model->top_level_item(section);
    bool is_checked = top_item->is_checked()
            && model->top_level_item(static_cast<int>(j_module_t::Linguist))->is_checked();
    if (!is_checked)
        return res;
    auto list = top_item->get_childs();
    foreach (auto item, list)
        if (item->is_checked())
            res |= handler_id_from_int(item->row());
    return res;
}

bool j_input_display::get_comp_settings() const
{
    int section = static_cast<int>(j_module_t::Comparator);
    const auto model = settings()->get_model();
    const auto top_item = model->top_level_item(section);
    bool is_checked = top_item->is_checked()
            && model->top_level_item(static_cast<int>(j_module_t::Linguist))->is_checked()
            && model->top_level_item(static_cast<int>(j_module_t::Processor))->is_checked();
    return is_checked;
}

const tree_settings_item *j_input_display::get_ling_settings_data() const
{
    int section = static_cast<int>(j_module_t::Linguist);
    return settings()->get_model()->top_level_item(section);
}

void j_input_display::rewrite_input_message(QList<j_ling> list)
{
    const auto top_item = get_ling_settings_data();
    foreach (auto ling, list)
    {
        int index = enum_to_int(ling.type);
        const auto item = top_item->child_at(index);
        if (index >= 0 && item->is_checked())
            add_word(ling.str, item->get_color());
    }
    add_word(" ->", top_item->child_at(enum_to_int(j_ling_type::Separator))->get_color());
    add_empty_string();
}

void j_input_display::process_input()
{
    QStringList msg_list = field()->toPlainText().split('\n', Qt::SkipEmptyParts);
    clear_field();
    if (msg_list.count() > 0)
    {
        Q_EMIT to_configure(msg_list.size());
        foreach (QString msg, msg_list)
            Q_EMIT to_analyse(msg);
    }
}
