#include "import/tree_settings_widget.h"

#include <QTreeView>
#include <QColorDialog>

tree_settings::settings_tree_model::settings_tree_model(QWidget* parent) : QAbstractItemModel(parent)
{
    parent_widget = parent;
}

tree_settings::settings_tree_model::~settings_tree_model()
{
    delete(root);
}

int tree_settings::settings_tree_model::rowCount(const QModelIndex &parent) const
{
    tree_settings_item *parent_it;
    if (parent.column() > 0)
        return 0;

    parent_it = (!parent.isValid()) ? root : static_cast<tree_settings_item*>(parent.internalPointer());
    return parent_it->child_count();
}

int tree_settings::settings_tree_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return static_cast<tree_settings_item*>(parent.internalPointer())->column_count();
    return root->column_count();
}

QModelIndex tree_settings::settings_tree_model::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    tree_settings_item *child_it = static_cast<tree_settings_item*>(index.internalPointer());
    tree_settings_item *parent_it = child_it->get_parent();

    if (parent_it == root)
        return QModelIndex();

    return createIndex(parent_it->row(), 0, parent_it);
}

QModelIndex tree_settings::settings_tree_model::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    tree_settings_item *parent_it = (!parent.isValid()) ? root : static_cast<tree_settings_item*>(parent.internalPointer());

    tree_settings_item *child_it = parent_it->child_at(row);
    if (child_it)
        return createIndex(row, column, child_it);
    return QModelIndex();
}

QVariant tree_settings::settings_tree_model::data(const QModelIndex &index, int role) const
{
    QVariant value;
    switch (role)
    {
    case Qt::DisplayRole:
    {
        value = static_cast<tree_settings_item*>(index.internalPointer())->name();
    }
    break;
    case Qt::CheckStateRole:
    {
        value = static_cast<tree_settings_item*>(index.internalPointer())->checkstate();
    }
    break;
    case Qt::ForegroundRole:
    {
        tree_settings_item* item = static_cast<tree_settings_item*>(index.internalPointer());
        value = (item->has_color()) ? item->get_color() : Qt::black;
    }
    break;
    case Qt::ToolTipRole:
    {
        tree_settings_item* item = static_cast<tree_settings_item*>(index.internalPointer());
        if (item->has_color())
            value = "Change highlight color on double click";
    }
    }
    return value;
}

bool tree_settings::settings_tree_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role != Qt::CheckStateRole)
        return false;
    tree_settings_item* item = static_cast<tree_settings_item*>(index.internalPointer());
    item->set_checkstate(value.toBool());
    Q_EMIT dataChanged(index, index);
    if (item->get_parent())
        Q_EMIT dataChanged(parent(index), parent(index));
    return true;
}

Qt::ItemFlags tree_settings::settings_tree_model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemFlag::NoItemFlags;
    return Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsUserCheckable;
}

QVariant tree_settings::settings_tree_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (root && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return root->name();

    return QVariant();
}

const tree_settings_item *tree_settings::settings_tree_model::top_level_item(int index) const
{
    return root->child_at(index);
}

void tree_settings::settings_tree_model::change_highlight_color(const QModelIndex &index)
{
    if (!index.isValid())
        return;
    tree_settings_item* item = static_cast<tree_settings_item*>(index.internalPointer());
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

tree_settings::tree_settings_widget::tree_settings_widget(settings_tree_model *_model, QWidget *parent) : QDockWidget(parent)
{
    tree = new QTreeView(this);
    model = _model;
    tree->setModel(model);
    connect(tree, &QAbstractItemView::doubleClicked, model, &settings_tree_model::change_highlight_color);
    setWidget(tree);
    setWindowTitle("Settings");
}

