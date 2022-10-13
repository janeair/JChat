#ifndef J_ACTION_TOOLBAR_H
#define J_ACTION_TOOLBAR_H

#include <QToolBar>

enum class j_toolbar_action_t
{
    A_SELECT,
    A_DELETE,
    A_SAVE,
    A_OPEN,
    A_IMPORT,
    A_EXPORT,
    A_SETTINGS,
    A_PROFILE,
    A_ADD_PROFILE,
    A_EDIT_PROFILE,

    COUNT,
};

QString enum_to_string(j_toolbar_action_t t);
QString enum_to_icon_path(j_toolbar_action_t t);

class j_action_toolbar : public QToolBar
{
    Q_OBJECT

public:
    j_action_toolbar(QString title = QString(), QWidget* parent = nullptr);
    ~j_action_toolbar() = default;
    template<typename T1, typename T2>
    void add_action(j_toolbar_action_t t, QString tooltip,
                    T1 *reciever, void (T1::*reciever_slot)(bool),
                    T2 *trigger, void (T2::*trigger_signal)(bool), bool default_enabled = true)
    {
        QIcon action_icon = QIcon(enum_to_icon_path(t));
        QAction* new_action = new QAction(action_icon, tooltip, this);
        new_action->setEnabled(default_enabled);
        new_action->setCheckable(true);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        connect(trigger, trigger_signal, new_action, &QAction::setEnabled);
        addAction(new_action);
    }
    template<typename T1, typename T2>
    void add_action(j_toolbar_action_t t, QString tooltip,
                    T1 *reciever, void (T1::*reciever_slot)(),
                    T2 *trigger, void (T2::*trigger_signal)(bool), bool default_enabled = true)
    {
        QIcon action_icon = QIcon(enum_to_icon_path(t));
        QAction* new_action = new QAction(action_icon, tooltip, this);
        new_action->setEnabled(default_enabled);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        connect(trigger, trigger_signal, new_action, &QAction::setEnabled);
        addAction(new_action);
    }
    template<typename T>
    void add_action(j_toolbar_action_t t, QString tooltip,
                    T *reciever, void (T::*reciever_slot)())
    {
        QIcon action_icon = QIcon(enum_to_icon_path(t));
        QAction* new_action = new QAction(action_icon, tooltip, this);
        new_action->setEnabled(true);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        addAction(new_action);
    }
    template<typename T>
    void add_action(j_toolbar_action_t t, QString tooltip,
                    T *reciever, void (T::*reciever_slot)(bool))
    {
        QIcon action_icon = QIcon(enum_to_icon_path(t));
        QAction* new_action = new QAction(action_icon, tooltip, this);
        new_action->setEnabled(true);
        new_action->setCheckable(true);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        addAction(new_action);
    }
};

#endif // J_ACTION_TOOLBAR_H
