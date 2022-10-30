#include "gui/display/settings/j_settings.h"

settings_item::settings_item(settings_item *_parent, const QString &name, QColor _color, bool default_checked)
{
    parent = _parent;
    title = name;
    state = (default_checked) ? Qt::Checked : Qt::Unchecked;
    color = _color;
}

settings_item::~settings_item()
{
    for (auto child : childs)
        delete(child);
}

void settings_item::add_child(settings_item *_child)
{
    childs.append(_child);
}

int settings_item::child_count() const
{
    return childs.size();
}

int settings_item::column_count() const
{
    return 1;
}

int settings_item::row() const
{
    if (parent)
        return parent->childs.indexOf(const_cast<settings_item*>(this));
    return 0;
}

void settings_item::set_checkstate(bool _state)
{
    state = (_state) ? Qt::Checked : Qt::Unchecked;
    for (auto child : childs)
        child->set_checkstate(_state);
    if (parent)
        parent->update_checkstate();
}

void settings_item::update_checkstate() const
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

settings_item *settings_item::child_at(int row)
{
    if (row < 0 || row >= childs.size())
        return nullptr;
    return childs.at(row);
}
