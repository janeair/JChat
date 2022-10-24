#ifndef J_PROFILE_EDITOR_H
#define J_PROFILE_EDITOR_H

#include <QAbstractTableModel>
#include <QMainWindow>

#include "common/stats/j_msgs_property_stats.h"
#include "gui/log/j_log_action.h"

class action_toolbar;
class j_profile;
class j_profile_base;
class QTableView;
class QLineEdit;
class QLabel;

enum class j_profile_editor_table_column_t
{
    profile_name,
    profile_type,
    profile_properties,

    COUNT
};

QString enum_to_string(j_profile_editor_table_column_t t);

class j_profile_editor_table_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    j_profile_editor_table_model(QObject* parent = nullptr);
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex&index) const override;

    void set_names_editable(bool edit);
    bool is_profile_in_base(const QString &p_name);
    bool delete_profile(const QString &p_name);
    void add_data(const QString &p_name, j_msgs_property_stats data);

signals:
    void log_this(j_log_action_t t, QString decr);

private:
    j_profile_base* base = nullptr;
    bool names_can_be_editable = false;

    void set_profile_base(j_profile_base* p_base);
    j_profile_base* get_base() { return base; }
    const j_profile_base* get_base() const { return base; }

    friend class j_profile_editor;
    friend class jchat_gui;
};

class j_profile_editor : public QMainWindow
{
    Q_OBJECT

public:
    j_profile_editor(QWidget* parent = nullptr);
    ~j_profile_editor() = default;
    j_profile_editor_table_model* get_data_model() { return table_model; }
    void set_profile_base(j_profile_base* base);

public slots:
    void delete_selected_profile();
    void open_selected_profile();
    void set_edit_profile_names(bool edit);
    void save_to_selected_profile();

    void set_current_stats(j_msgs_property_stats stats);
    void clear_current_stats();

protected slots:
    void closeEvent(QCloseEvent* event);

signals:
    void selected_profile_changed(bool is_in_base);
    void current_stats_changed(bool is_valid);

    void profile_to_display(const j_profile* p);

private:
    /// gui
    action_toolbar* toolbar                     = nullptr;
    QLineEdit* current_profile                  = nullptr;
    QTableView* profile_table                   = nullptr;
    QLabel* profiles_cc                         = nullptr;
    /// data
    j_profile_editor_table_model* table_model   = nullptr;
    j_msgs_property_stats current_stats;

};

#endif // J_PROFILE_EDITOR_H
