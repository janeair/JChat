#ifndef J_PROFILE_LOADER_H
#define J_PROFILE_LOADER_H

#include "common/stats/j_msgs_property_stats.h"

#include <QObject>
#include <QHash>

using PROFILE = QPair<QString, j_msgs_property_stats>;
using PROFILE_P = QPair<QString, j_msgs_property_stats*>;

class j_profile_loader : public QObject
{
    Q_OBJECT

public:
    j_profile_loader(QObject *parent = nullptr);
    void load_profiles();
    QStringList profiles_name_list() const;
    j_msgs_property_stats* profile_stats(QString name) const;

public slots:
    bool add(PROFILE pro);
    bool get_profile_from_gui(QString name);
    void save_profiles();

signals:
    void profiles_to_gui(QStringList profiles);
    void profile_data_to_gui(PROFILE_P profile);

private:
    QList<PROFILE_P>* profiles = nullptr;
    QHash<QString, int> name_to_list;

};

#endif // J_PROFILE_LOADER_H
