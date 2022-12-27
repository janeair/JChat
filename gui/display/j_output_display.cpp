#include "j_output_display.h"

#include "common/property/j_msg_property.h"
#include "common/j_stats_t.h"
#include "gui/common/j_action_toolbar.h"
#include "gui/log/j_log_action.h"
#include "gui/display/j_display_type.h"

#include <QTextEdit>

j_output_display::j_output_display(QWidget* parent)
    : j_abstract_display(
         j_display_type::output,
          parent
          )
{
    /// configure toolbar
    toolbar()->add_action<tree_checkable_settings_widget>
            (icon(j_toolbar_action_t::A_SETTINGS), "Show/hide settings", settings(), &tree_checkable_settings_widget::setVisible);
    toolbar()->add_action<j_output_display, j_output_display>
            (icon(j_toolbar_action_t::A_EXPORT), "Export to text file", this, &j_output_display::export_from_field, this, &j_output_display::field_text_changed, false);
    toolbar()->add_action<QTextEdit, j_output_display>
            (icon(j_toolbar_action_t::A_DELETE), "Clear field", field(), &QTextEdit::clear, this, &j_output_display::field_text_changed, false);

    /// configure field
    field()->setReadOnly(true);
    field()->setAlignment(Qt::AlignLeft);
}

QPair<bool, QColor> j_output_display::get_general_settings() const
{
    auto item = settings()->get_setting(enum_to_string(j_stats_t::general));
    return QPair<bool, QColor>(item->is_checked(), item->get_color());
}

const tree_checkable_settings_item* j_output_display::get_property_settings_data() const
{
    return settings()->get_setting(enum_to_string(j_stats_t::property));
}

const tree_checkable_settings_item* j_output_display::get_compare_settings_data() const
{
    return settings()->get_setting(enum_to_string(j_stats_t::compare));
}

void j_output_display::display_general_stats(const j_msgs_general_stats &stats)
{
    auto settings = get_general_settings();
    if (!settings.first)
        return;
    uint stats_count = enum_to_uint(j_msgs_general_stats_t::All);
    std::vector<uint32_t> stats_v = stats.statistics();
    add_string(enum_to_full_string(j_stats_t::general), settings.second);
    for (uint i = 0; i < stats_count; i++)
        add_tab_string(enum_to_string(uint_to_general_enum(i)) + ": " + QString::number(stats_v[i]), Qt::black);
    add_empty_string();
}

void j_output_display::display_property_stats(const j_msgs_property_stats &stats)
{
    auto st_data = get_property_settings_data();
    auto prop_list = stats.list();
    if (!st_data->is_checked() || prop_list.isEmpty())
        return;
    add_string(enum_to_full_string(j_stats_t::property), st_data->get_color());
    foreach (auto t, prop_list)
    {
        int id = t->id_int();
        auto item = st_data->child_at(id);
        if (item->is_checked())
        {
            j_simple_property* s_prop = static_cast<j_simple_property*>(t);
            add_tab_string(enum_to_string(s_prop->id_enum()) + " : " + QString::number(s_prop->data(), 'g', 3)
                            + " | weight: " + QString::number(s_prop->weight()), item->get_color());
        }
    }
    add_empty_string();
}

void j_output_display::display_profile(const j_profile *p)
{
    clear_field();
    add_string(p->get_name() + ":", Qt::black);
    display_property_stats(p->get_data());
    Q_EMIT log_this(j_log_action_t::OPEN_PROFILE, p->get_name());
}

void j_output_display::display_compare_results(QList<compare_result> list)
{
    auto st_data = get_compare_settings_data();
    if (!st_data->is_checked() || list.isEmpty())
        return;
    add_string(enum_to_full_string(j_stats_t::compare), st_data->get_color());
    foreach (auto res, list)
    {
        auto value = res.second;
        int index = static_cast<int>(compare_res_t_from_value(value));
        auto item = st_data->child_at(index);
        if (item->is_checked())
            add_tab_string(res.first + ": " + QString::number(res.second * 100, 'g', 3) + '%', item->get_color());
    }
    add_empty_string();
}
