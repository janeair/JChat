#include "import/tree_settings_item.h"

tree_checkable_settings_item::tree_checkable_settings_item(tree_checkable_settings_item *_parent, const QString &name, QColor _color, bool default_checked)
{
    parent = _parent;
    title = name;
    state = (default_checked) ? Qt::Checked : Qt::Unchecked;
    color = _color;
}

tree_checkable_settings_item::~tree_checkable_settings_item()
{
    for (auto child : childs)
        delete(child);
}

void tree_checkable_settings_item::add_child(tree_checkable_settings_item *_child)
{
    childs.append(_child);
}

int tree_checkable_settings_item::child_count() const
{
    return childs.size();
}

int tree_checkable_settings_item::column_count() const
{
    return 1;
}

int tree_checkable_settings_item::row() const
{
    if (parent)
        return parent->childs.indexOf(const_cast<tree_checkable_settings_item*>(this));
    return 0;
}

void tree_checkable_settings_item::set_checkstate(bool _state)
{
    state = (_state) ? Qt::Checked : Qt::Unchecked;
    for (auto child : childs)
        child->set_checkstate(_state);
    if (parent)
        parent->update_checkstate();
}

void tree_checkable_settings_item::set_color(const QColor &_color)
{
    color = _color;
}

void tree_checkable_settings_item::update_checkstate() const
{
    if (childs.size() == 0)
        return;
    bool is_all_checked = true;
    bool is_all_unchecked = true;
    for (auto child : childs)
    {
        is_all_checked &= child->is_checked();
        is_all_unchecked &= !child->is_checked();
    }
    Qt::CheckState updated_state = (is_all_checked) ? Qt::Checked : (is_all_unchecked) ? Qt::Unchecked : Qt::PartiallyChecked;
    if (updated_state != state)
    {
        state = updated_state;
        if (parent)
            parent->update_checkstate();
    }
}

tree_checkable_settings_item *tree_checkable_settings_item::child_at(int row)
{
    if (row < 0 || row >= childs.size())
        return nullptr;
    return childs.at(row);
}

const tree_checkable_settings_item *tree_checkable_settings_item::child_at(int row) const
{
    if (row < 0 || row >= childs.size())
        return nullptr;
    return childs.at(row);
}

///###############################################################

tree_checkable_settings_data::tree_checkable_settings_data(tree_checkable_settings_item *item)
{
    root = std::move(item);
    add_to_list(root);
}

const tree_checkable_settings_item *tree_checkable_settings_data::item(const QString &key) const
{
    return list.value(key, nullptr);
}

void tree_checkable_settings_data::add_to_list(tree_checkable_settings_item *item)
{
    foreach (auto child, item->get_childs())
        add_to_list(child);
    list.insert(item->name(), item);
}
