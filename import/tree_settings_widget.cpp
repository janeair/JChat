#include "import/tree_settings_widget.h"

#include <QTreeView>
#include <QColorDialog>

custom_settings::tree_checkable_settings_model::tree_checkable_settings_model(tree_checkable_settings_data* data, QWidget* parent) : QAbstractItemModel(parent)
{
    resource = data;
    parent_widget = parent;
}

custom_settings::tree_checkable_settings_model::~tree_checkable_settings_model()
{
    delete(resource);
}

int custom_settings::tree_checkable_settings_model::rowCount(const QModelIndex &parent) const
{
    tree_checkable_settings_item *parent_it;
    if (parent.column() > 0)
        return 0;

    parent_it = (!parent.isValid()) ? resource->head() : static_cast<tree_checkable_settings_item*>(parent.internalPointer());
    return parent_it->child_count();
}

int custom_settings::tree_checkable_settings_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return static_cast<tree_checkable_settings_item*>(parent.internalPointer())->column_count();
    return resource->head()->column_count();
}

QModelIndex custom_settings::tree_checkable_settings_model::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    tree_checkable_settings_item *child_it = static_cast<tree_checkable_settings_item*>(index.internalPointer());
    tree_checkable_settings_item *parent_it = child_it->get_parent();

    if (parent_it == resource->head())
        return QModelIndex();

    return createIndex(parent_it->row(), 0, parent_it);
}

QModelIndex custom_settings::tree_checkable_settings_model::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    tree_checkable_settings_item *parent_it = (!parent.isValid()) ? resource->head() : static_cast<tree_checkable_settings_item*>(parent.internalPointer());

    tree_checkable_settings_item *child_it = parent_it->child_at(row);
    if (child_it)
        return createIndex(row, column, child_it);
    return QModelIndex();
}

QVariant custom_settings::tree_checkable_settings_model::data(const QModelIndex &index, int role) const
{
    QVariant value;
    switch (role)
    {
    case Qt::DisplayRole:
    {
        value = static_cast<tree_checkable_settings_item*>(index.internalPointer())->name();
    }
    break;
    case Qt::CheckStateRole:
    {
        value = static_cast<tree_checkable_settings_item*>(index.internalPointer())->checkstate();
    }
    break;
    case Qt::ForegroundRole:
    {
        tree_checkable_settings_item* item = static_cast<tree_checkable_settings_item*>(index.internalPointer());
        value = (item->has_color()) ? item->get_color() : Qt::black;
    }
    break;
    case Qt::ToolTipRole:
    {
        tree_checkable_settings_item* item = static_cast<tree_checkable_settings_item*>(index.internalPointer());
        if (item->has_color())
            value = "Change highlight color on double click";
    }
    }
    return value;
}

bool custom_settings::tree_checkable_settings_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role != Qt::CheckStateRole)
        return false;
    tree_checkable_settings_item* item = static_cast<tree_checkable_settings_item*>(index.internalPointer());
    item->set_checkstate(value.toBool());
    Q_EMIT dataChanged(index, index);
    if (item->get_parent())
        Q_EMIT dataChanged(parent(index), parent(index));
    return true;
}

Qt::ItemFlags custom_settings::tree_checkable_settings_model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemFlag::NoItemFlags;
    return Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsUserCheckable;
}

QVariant custom_settings::tree_checkable_settings_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (resource->head() && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return resource->head()->name();

    return QVariant();
}

void custom_settings::tree_checkable_settings_model::change_highlight_color(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    tree_checkable_settings_item* item = static_cast<tree_checkable_settings_item*>(index.internalPointer());
    if (!item->has_color())
        return;
    if (!parent_widget)
        return;
    QColor color = QColorDialog::getColor(item->get_color(), parent_widget, "Change Highlight Color: " + item->name());
    if (color.isValid())
    {
        item->set_color(color);
        Q_EMIT dataChanged(index, index);
    }
}

///###############################################################

custom_settings::tree_checkable_settings_widget::tree_checkable_settings_widget(tree_checkable_settings_data *_data, QWidget *parent) : QDockWidget(parent)
{
    tree = new QTreeView(this);
    model = new tree_checkable_settings_model(_data, this);
    tree->setModel(model);
    connect(tree, &QAbstractItemView::doubleClicked, model, &tree_checkable_settings_model::change_highlight_color);
    setWidget(tree);
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setWindowTitle("Settings");
}


const tree_checkable_settings_item *custom_settings::tree_checkable_settings_widget::get_setting(const QString key) const
{
    return model->get_resource()->item(key);
}
