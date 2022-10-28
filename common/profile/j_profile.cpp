#include "common/profile/j_profile.h"

#include "common/stats/j_msgs_property_stats.h"

QString enum_to_string(j_profile_type t)
{
    switch (t)
    {
    case j_profile_type::loaded_normal:
        return QString("ok");
    case j_profile_type::loaded_error:
        return QString("error");
    case j_profile_type::created_user:
        return QString("user");
    case j_profile_type::created_default:
        return QString("default");
    default:
        return QString();
    }
}

QString enum_to_help_string(j_profile_type t) // tooltip role
{
    switch (t)
    {
    case j_profile_type::loaded_normal:
        return QString("Loaded as usual");
    case j_profile_type::loaded_error:
        return QString("Loaded with error");
    case j_profile_type::created_user:
        return QString("Created by user");
    case j_profile_type::created_default:
        return QString("Created by default");
    default:
        return QString();
    }
}

QColor enum_to_color(j_profile_type t)
{
    switch (t)
    {
    case j_profile_type::loaded_normal:
        return Qt::darkGreen;
    case j_profile_type::loaded_error:
        return Qt::darkRed;
    case j_profile_type::created_user:
        return Qt::darkBlue;
    case j_profile_type::created_default:
        return Qt::black;
    default:
        return Qt::black;
    }
}

j_profile::j_profile(const QString &p_name, j_profile_type p_type, j_msgs_property_stats p_data)
    : name(p_name), type(p_type), data(std::move(p_data)) { }

j_profile::~j_profile()
{
}

void j_profile::set_name(const QString &p_name)
{
    name = p_name;
}

void j_profile::set_data(j_msgs_property_stats p_data, j_profile_data_action action)
{
    switch (action)
    {
    case j_profile_data_action::replace:
    {
        data = std::move(p_data);
        break;
    }
    case j_profile_data_action::merge:
    {
        data.join(&p_data, j_stats_join_t::Merge);
        break;
    }
    default:
        break;
    }
}

///###############################################################

j_profile_base::j_profile_base(QObject *parent) : QObject(parent)
{
}

j_profile_base::~j_profile_base()
{
    for (auto p : profiles)
        delete(p);
}

const j_profile *j_profile_base::get_profile(const QString &name) const
{
    return name_to_profile.value(name, nullptr);
}

const j_msgs_property_stats j_profile_base::get_profile_data(const QString &name) const
{
    j_profile* p = name_to_profile.value(name, nullptr);
    if (p)
        return p->get_data();
    else
        return j_msgs_property_stats();
}

int j_profile_base::index(const QString &name) const
{
    auto p = name_to_profile.value(name, nullptr);
    if (p)
    {
        auto it = std::find_if(profiles.begin(), profiles.end(), [p] (j_profile* p_base) { return (p == p_base); });
        return it - profiles.begin();
    }
    else
        return -1;
}

const j_profile *j_profile_base::get_profile(int index) const
{
    return (index >= 0 && index < (int)profiles.size()) ? profiles.at(index) : nullptr;
}

bool j_profile_base::add_profile(j_profile *p_new)
{
    if (!p_new)
        return false;
    j_profile* p = name_to_profile.value(p_new->get_name(), nullptr);
    if (p)
    {
        p->set_data(p_new->get_data());
        delete(p_new);
    }
    else
    {
        profiles.push_back(p_new);
        name_to_profile.insert(p_new->get_name(), p_new);
        Q_EMIT profile_count_changed(profiles.size());
    }
    return true;
}

bool j_profile_base::add_data(const QString &p_name, j_msgs_property_stats p_data)
{
    j_profile* p = name_to_profile.value(p_name, nullptr);
    if (p)
        p->set_data(p_data);
    else
    {
        j_profile* p_new = new j_profile(p_name, j_profile_type::created_user, p_data);
        profiles.push_back(p_new);
        name_to_profile.insert(p_name, p_new);
        Q_EMIT profile_count_changed(profiles.size());
    }
    return true;
}

bool j_profile_base::rename_profile(j_profile *p, const QString &new_name)
{
    if (!p)
        return false;
    j_profile* p_base = name_to_profile.value(p->get_name(), nullptr);
    if (!p_base)
        p->set_name(new_name);
    else
    {
        p->set_name(new_name);
        p_base->set_name(new_name);
        p_base->set_type(j_profile_type::created_user);
        name_to_profile.remove(p->get_name());
        name_to_profile.insert(new_name, p_base);
    }
    return true;
}

bool j_profile_base::rename_profile(const QString &name, const QString &new_name)
{
    j_profile* p = name_to_profile.value(name, nullptr);
    if (!p)
        return false;
    else
    {
        p->set_name(new_name);
        p->set_type(j_profile_type::created_user);
        name_to_profile.remove(name);
        name_to_profile.insert(new_name, p);
    }
    return true;
}

bool j_profile_base::delete_profile(const QString &p_name)
{
    j_profile* p = name_to_profile.value(p_name, nullptr);
    if (!p)
        return false;
    else
    {
        auto it = std::remove_if(profiles.begin(), profiles.end(), [p] (j_profile* p_base) { return (p == p_base); });
        if (it != profiles.end())
        {
            profiles.erase(it);
            name_to_profile.remove(p->get_name());
            delete(p);
            Q_EMIT profile_count_changed(profiles.size());
        }
    }
    return true;
}

bool j_profile_base::delete_profile(j_profile *p)
{
    if (!p)
        return false;
    j_profile* p_base = name_to_profile.value(p->get_name(), nullptr);
    if (!p_base)
    {
        delete(p);
        return false;
    }
    else
    {
        auto it = std::remove_if(profiles.begin(), profiles.end(), [p] (j_profile* p_base) { return (p == p_base); });
        if (it != profiles.end())
        {
            profiles.erase(it);
            name_to_profile.remove(p_base->get_name());
            delete(p);
            Q_EMIT profile_count_changed(profiles.size());
        }
    }
    return true;
}

void j_profile_base::clear()
{
    foreach (auto *p, profiles)
        delete(p);
    profiles.clear();
    name_to_profile.clear();
    Q_EMIT profile_count_changed(profiles.size());
}
