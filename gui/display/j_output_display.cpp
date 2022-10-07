#include "j_output_display.h"

#include "gui/display/j_action_toolbar.h"
#include "gui/jchat_log.h"
#include "common/j_msg_property.h"

#include <QTextEdit>
#include <QDebug>

j_output_display::j_output_display(QWidget* parent)
    : j_abstract_display(
          QString("Output"),
          j_settings(j_settings_t::Lings | j_settings_t::General | j_settings_t::Properties),
          parent
          )
{
    /// configure toolbar
    toolbar()->add_action(j_toolbar_action_t::A_CHECKALL, "Select all settings");
    toolbar()->add_action(j_toolbar_action_t::A_CLEAR, "Clear field");
    toolbar()->add_action(j_toolbar_action_t::A_SAVE, "Save to profile");
    toolbar()->add_action(j_toolbar_action_t::A_OPEN, "Open from profile");

    dlg = new j_profile_dialog(this);
    connect(dlg, &j_profile_dialog::selected_profile, this, &j_output_display::on_selected_profile);
    connect(toolbar(), &j_action_toolbar::to_save, this, &j_output_display::save_to_profile_dialog);
    connect(toolbar(), &j_action_toolbar::to_open, this, &j_output_display::open_profile_dialog);
    connect(toolbar(), &j_action_toolbar::to_clear, [this] { current_stats.clear(); });

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

void j_output_display::display_general_stats(j_msgs_general_stats stats)
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

void j_output_display::display_property_stats(j_msgs_property_stats stats)
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

void j_output_display::display_profile(PROFILE_P profile)
{
    field()->clear();
    field()->setTextColor(Qt::black);
    field()->append(profile.first + ":");
    display_property_stats(*(profile.second));
    emit log_this(j_log_action_t::OPEN_PROFILE, profile.first);
}

void j_output_display::display_compare_results(QList<COMPARE_RES> list)
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

void j_output_display::save_property_stats(j_msgs_property_stats stats)
{
    current_stats.clear();
    current_stats.join(&stats, j_stats_join_t::Extend);
    display_property_stats(stats);
}

void j_output_display::on_change_profiles(QStringList profiles)
{
    loaded_profiles = profiles;
}

void j_output_display::save_to_profile_dialog()
{
    dlg->exec_profiles(loaded_profiles, j_profile_dialog_action::SaveNewProfile);
}

void j_output_display::open_profile_dialog()
{
    dlg->exec_profiles(loaded_profiles, j_profile_dialog_action::GetProfileData);
}

void j_output_display::on_selected_profile(j_profile_dialog_action action, QString name)
{
    switch(action)
    {
    case j_profile_dialog_action::GetProfileData:
    {
        emit get_profile_data(name);
        break;
    }
    case j_profile_dialog_action::SaveNewProfile:
    {
        if (!current_stats.is_clear())
        {
            emit new_profile(PROFILE(name, std::move(current_stats)));
            emit log_this(j_log_action_t::SAVE_PROFILE, name);
            current_stats.clear();
        }
        break;
    }
    case j_profile_dialog_action::None:
        break;
    }
}
