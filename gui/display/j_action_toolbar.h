#ifndef J_ACTION_TOOLBAR_H
#define J_ACTION_TOOLBAR_H

#include <QToolBar>
#include <QObject>

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
    QList<QAction*>* actions() { return action; }
    void clear_actions() { action->clear(); clear(); };
    void add_action(j_toolbar_action_t t, QString tooltip);

signals:
    void to_select();
    void to_delete();
    void to_save();
    void to_open();
    void to_import();
    void to_export();
    void to_settings();
    void to_profile();
    void to_add_profile();
    void to_edit_profile();

private:
    QList<QAction*>* action = nullptr;

    void connect_to(j_toolbar_action_t t, QAction* a);
};

#endif // J_ACTION_TOOLBAR_H
