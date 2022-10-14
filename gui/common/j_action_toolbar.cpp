#include "gui/display/j_action_toolbar.h"

QString enum_to_string(j_toolbar_action_t t)
{
    switch(t)
    {
    case j_toolbar_action_t::A_OPEN:
        return QString("Open");
    case j_toolbar_action_t::A_SAVE:
        return QString("Save");
    case j_toolbar_action_t::A_DELETE:
        return QString("Delete");
    case j_toolbar_action_t::A_EDIT:
        return QString("Edit");
    case j_toolbar_action_t::A_IMPORT:
        return QString("Import");
    case j_toolbar_action_t::A_EXPORT:
        return QString("Export");
    case j_toolbar_action_t::A_SETTINGS:
        return QString("Settings");
    case j_toolbar_action_t::A_SELECT:
        return QString("Select");
    case j_toolbar_action_t::A_PROFILE:
        return QString("Profile");
    case j_toolbar_action_t::A_ADD_PROFILE:
        return QString("Add Profile");
    case j_toolbar_action_t::A_EDIT_PROFILE:
        return QString("Edit Profile");
    default:
        return QString();
    }
}

QString enum_to_icon_path(j_toolbar_action_t t)
{
    switch(t)
    {
    case j_toolbar_action_t::A_OPEN:
        return QString(":/icons/resources/open_icon.png");
    case j_toolbar_action_t::A_SAVE:
        return QString(":/icons/resources/save_icon.png");
    case j_toolbar_action_t::A_DELETE:
        return QString(":/icons/resources/delete_icon.png");
    case j_toolbar_action_t::A_EDIT:
        return QString(":/icons/resources/edit_icon.png");
    case j_toolbar_action_t::A_IMPORT:
        return QString(":/icons/resources/import_icon.png");
    case j_toolbar_action_t::A_EXPORT:
        return QString(":/icons/resources/export_icon.png");
    case j_toolbar_action_t::A_SETTINGS:
        return QString(":/icons/resources/settings_icon.png");
    case j_toolbar_action_t::A_SELECT:
        return QString(":/icons/resources/select_icon.png");
    case j_toolbar_action_t::A_PROFILE:
        return QString(":/icons/resources/profile_icon.png");
    case j_toolbar_action_t::A_ADD_PROFILE:
        return QString(":/icons/resources/add_profile_icon.png");
    case j_toolbar_action_t::A_EDIT_PROFILE:
        return QString(":/icons/resources/edit_profile_icon.png");
    default:
        return QString();
    }
}

QIcon icon(j_toolbar_action_t t)
{
    return QIcon(enum_to_icon_path(t));
}
