#ifndef TREE_SETTINGS_ITEM_H
#define TREE_SETTINGS_ITEM_H

#include <QColor>
#include <QHash>

/// checkable string settings item with optional color

class tree_checkable_settings_item
{
public:
    explicit tree_checkable_settings_item(tree_checkable_settings_item *_parent,
                                          const QString &name,
                                          QColor _color = QColor(),
                                          bool default_checked = false);
    ~tree_checkable_settings_item();

    void add_child(tree_checkable_settings_item *_child);

    tree_checkable_settings_item *child_at(int row);
    const tree_checkable_settings_item *child_at(int row) const;
    tree_checkable_settings_item *get_parent() { return parent; };
    const QList<tree_checkable_settings_item*> get_childs() const { return childs; }
    int child_count() const;
    int column_count() const;
    int row() const;

    void set_checkstate(bool _state);
    void set_color(const QColor &_color);
    void update_checkstate() const;

    Qt::CheckState checkstate() const { return state; }
    bool is_checked() const { return state; }
    const QString &name() const { return title; }
    const QColor &get_color() const { return color; }
    bool has_color() const { return color.isValid(); }

private:
    tree_checkable_settings_item* parent = nullptr;
    QList<tree_checkable_settings_item*> childs;
    mutable Qt::CheckState state = Qt::Unchecked;
    QString title;
    QColor color;
};

class tree_checkable_settings_data
{
public:
    explicit tree_checkable_settings_data(tree_checkable_settings_item *item);
    ~tree_checkable_settings_data() { delete root; };
    const tree_checkable_settings_item* item(const QString& key) const;
    const tree_checkable_settings_item* head() const { return root; }
    tree_checkable_settings_item* head() { return root; }

private:
    tree_checkable_settings_item* root;
    QHash<QString, tree_checkable_settings_item*> list;

    void add_to_list (tree_checkable_settings_item* item);
};

#endif // TREE_SETTINGS_ITEM_H
