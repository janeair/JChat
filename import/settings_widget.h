#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include "import/settings_item.h"

#include <QDockWidget>
#include <QAbstractItemModel>

class QTreeView;

namespace tree_settings
{

// creates user accessible tree model with an empty root
// to use this: when inheriting this model create root item with all data needed
//              then call create_root to setup your root item in model

class settings_tree_model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit settings_tree_model(QWidget* parent = nullptr);
    ~settings_tree_model();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    const settings_item* top_level_item(int index) const;

protected:
    settings_item* get_root() { return root; }
    void create_root(settings_item* item) { root = item; }

public slots:
    void change_highlight_color(const QModelIndex& index);

private:
    settings_item* root = nullptr;
    QWidget* parent_widget = nullptr;
};

// creates tree widget with model/view structure
// supports change item' highlight color via creating color dialog on double click

class settings_widget : public QDockWidget
{
public:
    settings_widget(settings_tree_model* _model, QWidget* parent = nullptr);
    const settings_tree_model* get_model() const { return model; }

private:
    QTreeView* tree = nullptr;
    settings_tree_model* model = nullptr;

};

}

#endif // SETTINGS_WIDGET_H
