#ifndef TREE_SETTINGS_WIDGET_H
#define TREE_SETTINGS_WIDGET_H

#include "import/tree_settings_item.h"

#include <QDockWidget>
#include <QAbstractItemModel>

class QTreeView;

namespace custom_settings
{

// creates user accessible tree model with an empty root
// to use this: when inheriting this model create root item with all data needed
//              then call create_root to setup your root item in model

class tree_checkable_settings_model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit tree_checkable_settings_model(tree_checkable_settings_data *data, QWidget* parent = nullptr);
    ~tree_checkable_settings_model();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    const tree_checkable_settings_data* get_resource() const { return resource; }

public slots:
    void change_highlight_color(const QModelIndex& index);

private:
    tree_checkable_settings_data* resource = nullptr;
    QWidget* parent_widget = nullptr;
};

// creates tree widget with model/view structure
// supports change item' highlight color via creating color dialog on double click

class tree_checkable_settings_widget : public QDockWidget
{
public:
    tree_checkable_settings_widget(tree_checkable_settings_data *_data, QWidget* parent = nullptr);
    const tree_checkable_settings_item* get_setting(const QString key) const;

private:
    QTreeView* tree = nullptr;
    tree_checkable_settings_model* model = nullptr;

};

}

#endif // TREE_SETTINGS_WIDGET_H
