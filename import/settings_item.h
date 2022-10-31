#ifndef SETTINGS_ITEM_H
#define SETTINGS_ITEM_H

#include <QColor>

class settings_item
{
public:
    explicit settings_item(settings_item *_parent, const QString &name, QColor _color = QColor(), bool default_checked = false);
    ~settings_item();

    void add_child(settings_item *_child);

    settings_item *child_at(int row);
    settings_item *get_parent() { return parent; };
    const QList<settings_item*> get_childs() const { return childs; }
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
    settings_item* parent = nullptr;
    QList<settings_item*> childs;
    mutable Qt::CheckState state = Qt::Unchecked;
    QString title;
    QColor color;
};

#endif // SETTINGS_ITEM_H
