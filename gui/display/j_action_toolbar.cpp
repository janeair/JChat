#include "j_action_toolbar.h"

j_action_toolbar::j_action_toolbar(QString title, QWidget* parent) : QToolBar(title, parent)
{
    action = new QList<QAction*>();
}

j_action_toolbar::j_action_toolbar(j_toolbar_actions_t types, QString title, QWidget* parent) : QToolBar(title, parent)
{
    action = new QList<QAction*>();
    configure(types);
}

void j_action_toolbar::configure(j_toolbar_actions_t types)
{
    if (action)
        action->clear();
    else
        return;

    uint32_t len = static_cast<uint32_t>(j_toolbar_action_t::ALL);
    for (uint32_t i = 1; i < len; i = i << 1)
    {
        j_toolbar_action_t type = static_cast<j_toolbar_action_t>(i);
        if (types.testFlag(type))
            add_action(type, enum_to_string(type));
    }
}

void j_action_toolbar::add_action(j_toolbar_action_t t, QString tooltip)
{
    QIcon action_icon = QIcon(enum_to_icon_path(t));
    QAction* new_action = new QAction(action_icon, tooltip, this);
    connect_to(t, new_action);
    action->append(new_action);
    addAction(new_action);
}

void j_action_toolbar::connect_to(j_toolbar_action_t t, QAction *a)
{
    switch(t)
    {
    case j_toolbar_action_t::A_CLEAR:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_clear);
        return;
    case j_toolbar_action_t::A_OPEN:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_open);
        return;
    case j_toolbar_action_t::A_SAVE:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_save);
        return;
    case j_toolbar_action_t::A_PLAY:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_play);
        return;
    case j_toolbar_action_t::A_CHECKALL:
    {
        a->setCheckable(true);
        connect(a, &QAction::triggered, this, [this, a] { emit to_check_all(a->isChecked()); });
        return;
    }
    case j_toolbar_action_t::A_IMPORT:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_import);
        return;
    case j_toolbar_action_t::A_EXPORT:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_export);
        return;
    case j_toolbar_action_t::A_EDIT:
        connect(a, &QAction::triggered, this, &j_action_toolbar::to_edit);
        return;
    default:
        return;
    }
}

QString enum_to_string(j_toolbar_action_t t)
{
    switch(t)
    {
    case j_toolbar_action_t::A_CLEAR:
        return QString("Clear");
    case j_toolbar_action_t::A_OPEN:
        return QString("Open");
    case j_toolbar_action_t::A_SAVE:
        return QString("Save");
    case j_toolbar_action_t::A_PLAY:
        return QString("Play");
    case j_toolbar_action_t::A_CHECKALL:
        return QString("Select All");
    case j_toolbar_action_t::A_IMPORT:
        return QString("Import");
    case j_toolbar_action_t::A_EXPORT:
        return QString("Export");
    case j_toolbar_action_t::A_EDIT:
        return QString("Edit");
    default:
        return QString();
    }
}

QString enum_to_icon_path(j_toolbar_action_t t)
{
    switch(t)
    {
    case j_toolbar_action_t::A_CLEAR:
        return QString(":/icons/resources/clear_icon.ico");
    case j_toolbar_action_t::A_OPEN:
        return QString(":/icons/resources/open_file_icon.ico");
    case j_toolbar_action_t::A_SAVE:
        return QString(":/icons/resources/save_file_icon.ico");
    case j_toolbar_action_t::A_PLAY:
        return QString(":/icons/resources/play_icon.ico");
    case j_toolbar_action_t::A_CHECKALL:
        return QString(":/icons/resources/check_all_icon.ico");
    default:
        return QString();
    }
}
