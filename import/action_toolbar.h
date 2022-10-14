#ifndef ACTION_TOOLBAR_H
#define ACTION_TOOLBAR_H

#include <QToolBar>

class action_toolbar : public QToolBar
{
    Q_OBJECT

public:
    action_toolbar(QString title = QString(), QWidget* parent = nullptr)
        : QToolBar(title, parent) {};
    ~action_toolbar() = default;
    template<typename T1, typename T2>
    void add_action(QIcon icon, QString tooltip,
                    T1 *reciever, void (T1::*reciever_slot)(bool),
                    T2 *trigger, void (T2::*trigger_signal)(bool), bool default_enabled = true)
    {
        QAction* new_action = new QAction(icon, tooltip, this);
        new_action->setEnabled(default_enabled);
        new_action->setCheckable(true);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        connect(trigger, trigger_signal, new_action, &QAction::setEnabled);
        addAction(new_action);
    }
    template<typename T1, typename T2>
    void add_action(QIcon icon, QString tooltip,
                    T1 *reciever, void (T1::*reciever_slot)(),
                    T2 *trigger, void (T2::*trigger_signal)(bool), bool default_enabled = true)
    {
        QAction* new_action = new QAction(icon, tooltip, this);
        new_action->setEnabled(default_enabled);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        connect(trigger, trigger_signal, new_action, &QAction::setEnabled);
        addAction(new_action);
    }
    template<typename T>
    void add_action(QIcon icon, QString tooltip,
                    T *reciever, void (T::*reciever_slot)())
    {
        QAction* new_action = new QAction(icon, tooltip, this);
        new_action->setEnabled(true);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        addAction(new_action);
    }
    template<typename T>
    void add_action(QIcon icon, QString tooltip,
                    T *reciever, void (T::*reciever_slot)(bool))
    {
        QAction* new_action = new QAction(icon, tooltip, this);
        new_action->setEnabled(true);
        new_action->setCheckable(true);
        connect(new_action, &QAction::triggered, reciever, reciever_slot);
        addAction(new_action);
    }
};

#endif // ACTION_TOOLBAR_H
