#include "j_output_display.h"

#include "common/property/j_msg_property.h"
#include "gui/common/j_action_toolbar.h"
#include "gui/log/j_log_action.h"
#include "gui/display/settings/j_settings.h"

#include <QTextEdit>

j_output_display::j_output_display(QWidget* parent)
    : j_abstract_display(
          QString("Output"),
          j_settings(j_settings_t::Lings | j_settings_t::General | j_settings_t::Properties),
          parent
          )
{
    /// configure toolbar
    toolbar()->add_action<j_settings_widget>
            (icon(j_toolbar_action_t::A_SETTINGS), "Show/hide settings", settings_widget(), &j_settings_widget::setVisible);
    toolbar()->add_action<j_output_display, j_output_display>
            (icon(j_toolbar_action_t::A_EXPORT), "Export to text file", this, &j_output_display::export_from_field, this, &j_output_display::field_text_changed, false);
    toolbar()->add_action<QTextEdit, j_output_display>
            (icon(j_toolbar_action_t::A_DELETE), "Clear field", field(), &QTextEdit::clear, this, &j_output_display::field_text_changed, false);

    /// configure field
    field()->setReadOnly(true);
    field()->setAlignment(Qt::AlignLeft);
}

void j_output_display::display_lings(QList<j_ling> lings)
{
    auto settings = static_cast<j_ling_types>(settings_widget()->settings().get_settings(j_settings_t::Lings));
    if (settings.testFlag(j_ling_type::None))
        return;
    for (QList<j_ling>::const_iterator i = lings.cbegin(); i != lings.cend(); i++)
    {
        QString line("> ");
        if ((*i).type != j_ling_type::Separator && (*i).type != j_ling_type::ND)
        {
            field()->setTextColor(Qt::black);
            line += (*i).str + " ";
        }
        else
            field()->setTextColor(Qt::red);
        line += enum_to_string((*i).type);
        if ((*i).type == j_ling_type::Word)
            line += " " + enum_to_string((*i).lang);
        if (settings.testFlag((*i).type))
            field()->append(line);
    }
    field()->append("------------");
}

void j_output_display::display_general_stats(const j_msgs_general_stats &stats)
{
    auto settings = static_cast<j_msgs_general_stats_types>(settings_widget()->settings().get_settings(j_settings_t::General));
    if (settings.testFlag(j_msgs_general_stats_t::None))
        return;
    uint stats_count = enum_to_uint(j_msgs_general_stats_t::All);
    std::vector<uint32_t> stats_v = stats.statistics();
    assert(stats_v.size() == stats_count);
    field()->setTextColor(Qt::black);
    for (uint i = 0; i < stats_count; i++)
    {
        if (settings.testFlag(uint_to_general_enum(i)))
            field()->append("> " + enum_to_string(uint_to_general_enum(i))
                       + ": " + QString::number(stats_v[i]));
    }
    field()->append("------------");
}

void j_output_display::display_property_stats(const j_msgs_property_stats &stats)
{
    auto settings = static_cast<j_property_ids>(settings_widget()->settings().get_settings(j_settings_t::Properties));
    if (settings.testFlag(j_property_id::NONE))
        return;
    auto prop_list = stats.list();
    field()->setTextColor(Qt::darkBlue);
    foreach (j_abstract_property* t, prop_list)
    {
        if (settings.testFlag(t->id_enum()))
        {
            if (t->is_simple()) /// simple property parsing
            {
                j_simple_property* s_prop = static_cast<j_simple_property*>(t);
                field()->append("> " + enum_to_string(s_prop->id_enum()) + " : "
                        + QString::number(s_prop->data(), 'g', 3) + " | weight: " + QString::number(s_prop->weight()));
            }
            else                /// complex property parsing
            {

            }
        }
    }
    field()->setTextColor(Qt::black);
    field()->append("------------");
}

void j_output_display::display_profile(const j_profile *p)
{
    field()->clear();
    field()->setTextColor(Qt::black);
    field()->append(p->get_name() + ":");
    display_property_stats(p->get_data());
    Q_EMIT log_this(j_log_action_t::OPEN_PROFILE, p->get_name());
}

void j_output_display::display_compare_results(QList<compare_result> list)
{
    if (list.count() > 0)
    {
        field()->setTextColor(Qt::darkGreen);
        foreach (auto res, list)
            field()->append("> " + res.first + ": " + QString::number(res.second * 100, 'g', 3) + '%');
        field()->setTextColor(Qt::black);
        field()->append("------------");
    }
}
