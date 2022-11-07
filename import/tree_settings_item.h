#ifndef tree_settings_item_H
#define tree_settings_item_H

#include <QColor>

class tree_settings_item
{
public:
    explicit tree_settings_item(tree_settings_item *_parent, const QString &name, QColor _color = QColor(), bool default_checked = false);
    ~tree_settings_item();

    void add_child(tree_settings_item *_child);

    tree_settings_item *child_at(int row);
    const tree_settings_item *child_at(int row) const;
    tree_settings_item *get_parent() { return parent; };
    const QList<tree_settings_item*> get_childs() const { return childs; }
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
    tree_settings_item* parent = nullptr;
    QList<tree_settings_item*> childs;
    mutable Qt::CheckState state = Qt::Unchecked;
    QString title;
    QColor color;
};

#endif // tree_settings_item_H
