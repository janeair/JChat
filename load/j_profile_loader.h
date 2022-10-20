#ifndef J_PROFILE_LOADER_H
#define J_PROFILE_LOADER_H

#include "common/profile/j_profile.h"

#include <QObject>

class j_profile_loader : public QObject
{
    Q_OBJECT

public:
    j_profile_loader(QObject *parent = nullptr);
    j_profile_base* get_base() { return base.get(); }
    void load_profiles();

public slots:
    void save_profiles();

signals:

private:
    std::unique_ptr<j_profile_base> base;

};

#endif // J_PROFILE_LOADER_H
