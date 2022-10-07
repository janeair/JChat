#include "j_profile_loader.h"

j_profile_loader::j_profile_loader(QObject *parent) : QObject(parent)
{
    profiles = new QList<PROFILE_P>();
}

void j_profile_loader::load_profiles()
{

}

QStringList j_profile_loader::profiles_name_list() const
{
    QStringList names;
    foreach (auto name, *profiles)
        names.append(name.first);
    return names;
}

j_msgs_property_stats *j_profile_loader::profile_stats(QString name) const
{
    int pos = name_to_list.value(name, -1);
    if (pos == -1)
        return nullptr;
    else
        return profiles->at(pos).second;
}

bool j_profile_loader::add(PROFILE pro)
{
    int pos = name_to_list.value(pro.first, -1);
    if (pos == -1)
    {
        profiles->append(PROFILE_P(pro.first, new j_msgs_property_stats(pro.second)));
        name_to_list.insert(pro.first, profiles->size() - 1);
        emit profiles_to_gui(profiles_name_list());
        return true;
    }
    else
    {
        auto res = profiles->at(pos).second->join(&(pro.second), j_stats_join_t::Merge);
        return res;
    }
}

bool j_profile_loader::get_profile_from_gui(QString name)
{
    int pos = name_to_list.value(name, -1);
    if (pos == -1)
        return false;
    else
        emit profile_data_to_gui(profiles->at(pos));
    return true;
}

void j_profile_loader::save_profiles()
{

}
