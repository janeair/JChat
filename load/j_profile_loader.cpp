#include "j_profile_loader.h"

j_profile_loader::j_profile_loader(QObject *parent) : QObject(parent)
{
    base = std::make_unique<j_profile_base>();
}

void j_profile_loader::load_profiles()
{

}

void j_profile_loader::save_profiles()
{

}
