#ifndef tree_settings_widget_H
#define tree_settings_widget_H

#include "import/tree_settings_item.h"

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

    const tree_settings_item* top_level_item(int index) const;

protected:
    tree_settings_item* get_root() { return root; }
    void create_root(tree_settings_item* item) { root = item; }

public slots:
    void change_highlight_color(const QModelIndex& index);

private:
    tree_settings_item* root = nullptr;
    QWidget* parent_widget = nullptr;
};

// creates tree widget with model/view structure
// supports change item' highlight color via creating color dialog on double click

class tree_settings_widget : public QDockWidget
{
public:
    tree_settings_widget(settings_tree_model* _model, QWidget* parent = nullptr);
    const settings_tree_model* get_model() const { return model; }

private:
    QTreeView* tree = nullptr;
    settings_tree_model* model = nullptr;

};

}

#endif // tree_settings_widget_H
