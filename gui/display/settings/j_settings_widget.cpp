#include "j_settings_widget.h"

#include "gui/display/j_display_type.h"
#include "common/j_module_t.h"
#include "common/j_stats_t.h"
#include "common/ling/j_ling.h"
#include "common/property/j_msg_property.h"
#include "proc/handlers/j_ling_abstract_handler.h"

#include <QTreeView>

j_settings_tree_model::j_settings_tree_model(j_display_type t)
{
    switch (t)
    {
    case j_display_type::input:
    {
        root = new settings_item(nullptr, "Modules");
        auto count = static_cast<int>(j_module_t::COUNT);
        for (int i = 0; i < count; i++)
        {
            j_module_t type = static_cast<j_module_t>(i);
            QString name = enum_to_string(type);
            settings_item* top_item = new settings_item(root, name);
            switch (type)
            {
            case j_module_t::Linguist:
                {
                    auto count = static_cast<int>(j_ling_type::All);
                    for (int i = 1; i < count; i = i << 1)
                    {
                        j_ling_type type = static_cast<j_ling_type>(i);
                        QString name = enum_to_string(type);
                        settings_item* item = new settings_item(top_item, name, enum_to_default_color(type));
                        top_item->add_child(item);
                    }
                }
                break;
            case j_module_t::Processor:
                {
                    auto count = static_cast<int>(j_handler_id::AllHandlers) + 1;
                    for (int i = 1; i < count; i = i << 1)
                    {
                        j_handler_id type = static_cast<j_handler_id>(i);
                        QString name = enum_to_string(type);
                        settings_item* item = new settings_item(top_item, name);
                        top_item->add_child(item);
                    }
                }
                break;
            default:
                break;
            }
            root->add_child(top_item);
        }
    }
    break;
    case j_display_type::output:
    {
        root = new settings_item(nullptr, "Stats");
        auto count = static_cast<int>(j_stats_t::COUNT);
        for (int i = 0; i < count; i++)
        {
            j_stats_t type = static_cast<j_stats_t>(i);
            QString name = enum_to_string(type);
            settings_item* top_item = new settings_item(root, name, enum_to_default_color(type));
            if (type == j_stats_t::property)
            {
                auto count = static_cast<int>(j_property_id::COUNT);
                for (int i = 0; i < count; i++)
                {
                    j_property_id type = static_cast<j_property_id>(i);
                    QString name = enum_to_string(type);
                    settings_item* item = new settings_item(top_item, name);
                    top_item->add_child(item);
                }
            }
            root->add_child(top_item);
        }
    }
    break;
    }
}

j_settings_tree_model::~j_settings_tree_model()
{
    delete(root);
}

int j_settings_tree_model::rowCount(const QModelIndex &parent) const
{
    settings_item *parent_it;
    if (parent.column() > 0)
        return 0;

    parent_it = (!parent.isValid()) ? root : static_cast<settings_item*>(parent.internalPointer());
    return parent_it->child_count();
}

int j_settings_tree_model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return static_cast<settings_item*>(parent.internalPointer())->column_count();
    return root->column_count();
}

QModelIndex j_settings_tree_model::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    settings_item *child_it = static_cast<settings_item*>(index.internalPointer());
    settings_item *parent_it = child_it->get_parent();

    if (parent_it == root)
        return QModelIndex();

    return createIndex(parent_it->row(), 0, parent_it);
}

QModelIndex j_settings_tree_model::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    settings_item *parent_it = (!parent.isValid()) ? root : static_cast<settings_item*>(parent.internalPointer());

    settings_item *child_it = parent_it->child_at(row);
    if (child_it)
        return createIndex(row, column, child_it);
    return QModelIndex();
}

QVariant j_settings_tree_model::data(const QModelIndex &index, int role) const
{
    QVariant value;
    switch (role)
    {
    case Qt::DisplayRole:
    {
        value = static_cast<settings_item*>(index.internalPointer())->name();
    }
    break;
    case Qt::CheckStateRole:
    {
        value = static_cast<settings_item*>(index.internalPointer())->checkstate();
    }
    break;
    case Qt::ForegroundRole:
    {
        settings_item* item = static_cast<settings_item*>(index.internalPointer());
        value = (item->has_color()) ? item->get_color() : Qt::black;
    }
    break;
    }
    return value;
}

bool j_settings_tree_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role != Qt::CheckStateRole)
        return false;
    settings_item* item = static_cast<settings_item*>(index.internalPointer());
    item->set_checkstate(value.toBool());
    Q_EMIT dataChanged(index, index);
    if (item->get_parent())
        Q_EMIT dataChanged(parent(index), parent(index));
    return true;
}

Qt::ItemFlags j_settings_tree_model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemFlag::NoItemFlags;
    return Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsUserCheckable;
}

QVariant j_settings_tree_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return root->name();

    return QVariant();
}

///###############################################################

j_settings_widget::j_settings_widget(j_display_type t, QWidget *parent) : QDockWidget(parent)
{
    tree = new QTreeView(this);
    model = new j_settings_tree_model(t);
    tree->setModel(model);
    setWidget(tree);
    setWindowTitle("Settings");
}

