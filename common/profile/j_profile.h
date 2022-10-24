#ifndef J_PROFILE_H
#define J_PROFILE_H

#include <QString>
#include <QHash>
#include <QSet>
#include <QColor>
#include <QObject>

#include "common/stats/j_msgs_property_stats.h"

class j_msgs_property_stats;

enum class j_profile_type
{
    loaded_normal,
    loaded_error,
    created_user,
    created_default,
};

QString enum_to_string(j_profile_type t);
QColor enum_to_color(j_profile_type t);

enum class j_profile_data_action
{
    replace,
    merge,
};

class j_profile
{
public:
    j_profile(const QString &p_name,
              j_profile_type p_type,
              j_msgs_property_stats p_data);
    ~j_profile();
    const QString get_name() const { return name; }
    j_profile_type get_type() const { return type; }
    j_msgs_property_stats get_data() { return data; }
    const j_msgs_property_stats get_data() const { return data; }
    int get_property_count() const { return data.count(); }
    void set_type(j_profile_type p_type) { type = p_type; }
    bool is_valid() { return (type != j_profile_type::created_default) && (type != j_profile_type::loaded_error); }

private:
    QString name;
    j_profile_type type         = j_profile_type::created_default;
    j_msgs_property_stats data;

    void set_name(const QString &p_name);
    void set_data(j_msgs_property_stats p_data, j_profile_data_action action = j_profile_data_action::merge);

    friend class j_profile_base;
};

class j_profile_base : public QObject
{
    Q_OBJECT

public:
    j_profile_base(QObject* parent = nullptr);
    ~j_profile_base();
    const std::vector<j_profile*> get_profiles() const { return profiles; }
    const j_profile *get_profile(const QString &name) const;
    const j_msgs_property_stats get_profile_data(const QString &name) const;
    int count() const { return profiles.size(); }
    int index(const QString& name) const;
    const j_profile *get_profile(int index) const;

signals:
    void profile_count_changed(int count);

private:
    std::vector<j_profile*> profiles;
    QHash<QString, j_profile*> name_to_profile;

    bool rename_profile(j_profile* p, const QString &new_name);
    bool rename_profile(const QString &name, const QString &new_name);

    bool delete_profile(const QString &p_name);
    bool delete_profile(j_profile* p);

    bool add_profile(j_profile* p_new);
    bool add_data(const QString &p_name, j_msgs_property_stats p_data);

    void clear();

    friend class j_profile_loader;
    friend class j_profile_editor_table_model;
};

#endif // J_PROFILE_H
