#ifndef J_ACTION_TOOLBAR_H
#define J_ACTION_TOOLBAR_H

#include <QToolBar>
#include <QObject>

enum class j_toolbar_action_t
{
    NONE = 0x0,
    A_PLAY = 0x1,
    A_CHECKALL = 0x2,
    A_CLEAR = 0x4,
    A_SAVE = 0x8,
    A_OPEN = 0x10,
    A_IMPORT = 0x20,
    A_EXPORT = 0x40,
    A_EDIT = 0x80,
    ALL = 0xFF,
};

QString enum_to_string(j_toolbar_action_t t);
QString enum_to_icon_path(j_toolbar_action_t t);

Q_DECLARE_FLAGS(j_toolbar_actions_t, j_toolbar_action_t);

class j_action_toolbar : public QToolBar
{
    Q_OBJECT

public:
    j_action_toolbar(QString title = QString(), QWidget* parent = nullptr);
    j_action_toolbar(j_toolbar_actions_t types, QString title = QString(), QWidget* parent = nullptr);
    ~j_action_toolbar() = default;
    QList<QAction*>* actions() { return action; }
    void configure(j_toolbar_actions_t types);
    void add_action(j_toolbar_action_t t, QString tooltip);

signals:
    void to_play();
    void to_clear();
    void to_save();
    void to_open();
    void to_check_all(bool state);
    void to_import();
    void to_export();
    void to_edit();

private:
    QList<QAction*>* action = nullptr;

    void connect_to(j_toolbar_action_t t, QAction* a);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(j_toolbar_actions_t);

#endif // J_ACTION_TOOLBAR_H
