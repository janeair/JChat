#ifndef J_PROFILE_EDITOR_H
#define J_PROFILE_EDITOR_H

#include <QAbstractTableModel>
#include <QMainWindow>

class action_toolbar;
class j_profile_base;
class QTableView;
class QLineEdit;
class QLabel;

class j_profile_editor_table_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    j_profile_editor_table_model(QObject* parent = nullptr);
    void set_profile_base(j_profile_base* p_base) { base = p_base; }

private:
    j_profile_base* base = nullptr;

};

class j_profile_editor : public QMainWindow
{
    Q_OBJECT

public:
    j_profile_editor(QWidget* parent = nullptr);
    ~j_profile_editor() = default;
    j_profile_editor_table_model* get_data_model() { return table_model; }

protected slots:
    void closeEvent(QCloseEvent* event);

signals:
    void selected_profile(QString name);

private:
    /// gui
    action_toolbar* toolbar                     = nullptr;
    QLineEdit* current_profile                  = nullptr;
    QTableView* profile_table                   = nullptr;
    QLabel* profiles_cc                         = nullptr;
    /// data
    j_profile_editor_table_model* table_model   = nullptr;
};

#endif // J_PROFILE_EDITOR_H
