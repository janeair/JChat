#ifndef J_SETTINGS_H
#define J_SETTINGS_H

#include "common/j_ling.h"
#include "common/j_module_t.h"
#include "common/j_msg_property.h"
#include "common/j_msgs_general_stats.h"
#include "proc/handlers/j_ling_abstract_handler.h"

#include <QDockWidget>
#include <QHash>

class QTreeWidget;
class QTreeWidgetItem;

enum class j_settings_t
{
    None = 0x0,
    Lings = 0x1,
    Handlers = 0x2,
    Modules = 0x4,
    General = 0x8,
    Properties = 0x10,
    All = 0x1F,
};

QString enum_to_string(j_settings_t t);
uint32_t enum_to_settings_all_flag(j_settings_t t);

Q_DECLARE_FLAGS(j_settings_types, j_settings_t);
Q_DECLARE_OPERATORS_FOR_FLAGS(j_settings_types);

class j_settings
{
public:
    j_settings(j_settings_types types);
    bool has_settings(j_settings_t t);
    uint32_t get_settings(j_settings_t t);
    QList<QPair<j_settings_t, uint32_t>> settings() { return st; }
    void set_flags(j_settings_t t, uint32_t value);
    void remove_flags(j_settings_t t, uint32_t value);

private:
    QList<QPair<j_settings_t, uint32_t>> st;
};

class j_settings_widget : public QDockWidget
{
public:
    j_settings_widget(j_settings t, QWidget* parent = nullptr);
    ~j_settings_widget() = default;

    j_settings settings() const { return st; }

public slots:
    void update_settings(QTreeWidgetItem *item, int column = 0);
    void check_all(bool state);

private:
    QTreeWidget* tree = nullptr;
    QList<QTreeWidgetItem*> st_list;
    j_settings st;
    QHash<QTreeWidgetItem*, QPair<j_settings_t, uint32_t>> hash;
};

#endif // J_SETTINGS_H
