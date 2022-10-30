#ifndef J_SETTINGS_WIDGET_H
#define J_SETTINGS_WIDGET_H

#include "gui/display/settings/j_settings.h"

#include <QDockWidget>
#include <QAbstractItemModel>

enum class j_display_type;

class QTreeView;

class j_settings_tree_model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit j_settings_tree_model(j_display_type t);
    ~j_settings_tree_model();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    settings_item* root = nullptr;
};

class j_settings_widget : public QDockWidget
{
public:
    j_settings_widget(j_display_type t, QWidget* parent = nullptr);

private:
    QTreeView* tree = nullptr;
    j_settings_tree_model* model = nullptr;

};

#endif // J_SETTINGS_WIDGET_H
