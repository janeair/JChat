#include "j_action_toolbar.h"

j_action_toolbar::j_action_toolbar(QString title, QWidget* parent) : QToolBar(title, parent)
{
    action = new QList<ACTION>();
}

void j_action_toolbar::add_action(j_toolbar_action_t t, QString tooltip, bool default_enabled)
{
    QIcon action_icon = QIcon(enum_to_icon_path(t));
    QAction* new_action = new QAction(action_icon, tooltip, this);
    new_action->setEnabled(default_enabled);
    connect_to(t, new_action);
    action->append(ACTION(t, new_action));
    addAction(new_action);
}

void j_action_toolbar::set_enabled(j_toolbar_action_t t, bool value)
{
    foreach (ACTION a, actions())
        if (a.first == t)
        {
            a.second->setEnabled(value);
            return;
        }
}

void j_action_toolbar::connect_to(j_toolbar_action_t t, QAction *a)
{
    switch(t)
    {
    case j_toolbar_action_t::A_SELECT:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_select);
        return;
    case j_toolbar_action_t::A_DELETE:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_delete);
        return;
    case j_toolbar_action_t::A_OPEN:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_open);
        return;
    case j_toolbar_action_t::A_SAVE:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_save);
        return;
    case j_toolbar_action_t::A_IMPORT:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_import);
        return;
    case j_toolbar_action_t::A_EXPORT:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_export);
        return;
    case j_toolbar_action_t::A_SETTINGS:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_settings);
        return;
    case j_toolbar_action_t::A_PROFILE:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_profile);
        return;
    case j_toolbar_action_t::A_ADD_PROFILE:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_add_profile);
        return;
    case j_toolbar_action_t::A_EDIT_PROFILE:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_edit_profile);
        return;
    default:
        return;
    }
}

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
