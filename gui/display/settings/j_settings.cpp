#include "gui/display/settings/j_settings.h"

#include <QCheckBox>
#include <QTreeWidget>

#include <QDebug>

j_settings_widget::j_settings_widget(j_settings t, QWidget *parent)
    : QDockWidget(parent), st(t)
{
    tree = new QTreeWidget(this);
    tree->setColumnCount(1);
    tree->setHeaderHidden(true);
    connect(tree, &QTreeWidget::itemClicked, this, &j_settings_widget::update_settings);

    uint32_t len = static_cast<uint32_t>(j_settings_t::All);
    for (uint32_t i = 1; i < len; i = i << 1)
    {
        j_settings_t type = static_cast<j_settings_t>(i);
        if (st.has_settings(type))
        {
            QTreeWidgetItem* top = new QTreeWidgetItem();
            top->setText(0, enum_to_string(type));
            top->setCheckState(0, Qt::Checked);

            switch (type)
            {
            case j_settings_t::Lings:
                {
                    uint32_t len = enum_to_settings_all_flag(j_settings_t::Lings);
                    for (uint32_t i = 1; i < len; i = i << 1)
                    {
                        j_ling_type t = static_cast<j_ling_type>(i);
                        QTreeWidgetItem* it = new QTreeWidgetItem();
                        it->setText(0, enum_to_string(t));
                        it->setCheckState(0, Qt::Checked);
                        top->addChild(it);
                        st_list.append(it);
                        hash.insert(it, QPair<j_settings_t, uint32_t>(type, i));
                    }
                }
            break;
            case j_settings_t::Modules:
                {
                    uint32_t len = enum_to_settings_all_flag(j_settings_t::Modules);
                    for (uint32_t i = 1; i < len; i = i << 1)
                    {
                        j_module_t t = static_cast<j_module_t>(i);
                        QTreeWidgetItem* it = new QTreeWidgetItem();
                        it->setText(0, enum_to_string(t));
                        it->setCheckState(0, Qt::Checked);
                        top->addChild(it);
                        st_list.append(it);
                        hash.insert(it, QPair<j_settings_t, uint32_t>(type, i));
                    }
                }
            break;
            case j_settings_t::Handlers:
                {
                    uint32_t len = enum_to_settings_all_flag(j_settings_t::Handlers);
                    for (uint32_t i = 1; i < len; i = i << 1)
                    {
                        j_handler_id t = static_cast<j_handler_id>(i);
                        QTreeWidgetItem* it = new QTreeWidgetItem();
                        it->setText(0, enum_to_string(t));
                        it->setCheckState(0, Qt::Checked);
                        top->addChild(it);
                        st_list.append(it);
                        hash.insert(it, QPair<j_settings_t, uint32_t>(type, i));
                    }
                }
            break;
            case j_settings_t::General:
                {
                    uint32_t len = enum_to_settings_all_flag(j_settings_t::General);
                    for (uint32_t i = 1; i < len; i = i << 1)
                    {
                        j_msgs_general_stats_t t = static_cast<j_msgs_general_stats_t>(i);
                        QTreeWidgetItem* it = new QTreeWidgetItem();
                        it->setText(0, enum_to_string(t));
                        it->setCheckState(0, Qt::Checked);
                        top->addChild(it);
                        st_list.append(it);
                        hash.insert(it, QPair<j_settings_t, uint32_t>(type, i));
                    }
                }
            break;
            case j_settings_t::Properties:
                {
                    uint32_t len = enum_to_settings_all_flag(j_settings_t::Properties);
                    for (uint32_t i = 1; i < len; i = i << 1)
                    {
                        j_property_id t = static_cast<j_property_id>(i);
                        QTreeWidgetItem* it = new QTreeWidgetItem();
                        it->setText(0, enum_to_string(t));
                        it->setCheckState(0, Qt::Checked);
                        top->addChild(it);
                        st_list.append(it);
                        hash.insert(it, QPair<j_settings_t, uint32_t>(type, i));
                    }
                }
            break;
            default:
            break;
            }

            st_list.append(top);
            tree->addTopLevelItem(top);
            hash.insert(top, QPair<j_settings_t, uint32_t>(type, enum_to_settings_all_flag(type)));
        }
    }

    setWidget(tree);
    setWindowTitle("Settings");
}

void j_settings_widget::update_settings(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem* parent = item->parent();
    bool state = item->checkState(column);
    auto pair = hash.value(item);
    if (parent)
    {
        if (state)
            st.set_flags(pair.first, pair.second);
        else
            st.remove_flags(pair.first, pair.second);
        qDebug() << parent->text(column) << item->text(column) << state;

    }
    else
    {
        int count = item->childCount();
        for (int i = 0; i < count; i++)
            item->child(i)->setDisabled(!state);
        qDebug() << item->text(column) << state;
    }

}

void j_settings_widget::check_all(bool state)
{
    Qt::CheckState cb_state = (state) ? Qt::Checked : Qt::Unchecked;
    /// check/uncheck all child items in tree
    for (QList<QTreeWidgetItem*>::iterator item = st_list.begin(); item != st_list.end(); ++item)
    {
        /// only for child items
        if ((*item)->parent())
        {
            (*item)->setCheckState(0, cb_state);
            update_settings((*item), 0);
        }
    }
}

QString enum_to_string(j_settings_t t)
{
    switch(t)
    {
    case j_settings_t::Lings:
        return QString("Lings");
    case j_settings_t::Handlers:
        return QString("Handlers");
    case j_settings_t::Modules:
        return QString("Modules");
    case j_settings_t::General:
        return QString("General Stats");
    case j_settings_t::Properties:
        return QString("Properties");
    default:
        return QString();
    }
}

j_settings::j_settings(j_settings_types types)
{
    uint32_t len = static_cast<uint32_t>(j_settings_t::All);
    for (uint32_t i = 1; i < len; i = i << 1)
    {
        j_settings_t type = static_cast<j_settings_t>(i);
        if (types.testFlag(type))
        {
            st.append(QPair<j_settings_t, uint32_t>(type, enum_to_settings_all_flag(type)));
        }
    }
}

bool j_settings::has_settings(j_settings_t t)
{
    foreach (auto i, st)
        if (i.first == t)
            return true;
    return false;
}

uint32_t j_settings::get_settings(j_settings_t t)
{
    foreach (auto i, st)
        if (i.first == t)
            return i.second;
    return 0;
}

void j_settings::remove_flags(j_settings_t t, uint32_t value)
{
    for (QList<QPair<j_settings_t, uint32_t>>::iterator i = st.begin(); i != st.end(); ++i)
        if (i->first == t)
        {
            i->second = i->second & ~value;
        }
    return;
}

void j_settings::set_flags(j_settings_t t, uint32_t value)
{
    for (QList<QPair<j_settings_t, uint32_t>>::iterator i = st.begin(); i != st.end(); ++i)
        if (i->first == t)
        {
            i->second = i->second | value;
        }
    return;
}

uint32_t enum_to_settings_all_flag(j_settings_t t)
{
    switch(t)
    {
    case j_settings_t::Lings:
        return static_cast<uint32_t>(j_ling_type::All);
    case j_settings_t::Handlers:
        return (static_cast<uint32_t>(j_handler_id::AllHandlers));
    case j_settings_t::Modules:
        return static_cast<uint32_t>(j_module_t::All);
    case j_settings_t::General:
        return static_cast<uint32_t>(j_msgs_general_stats_t::All);
    case j_settings_t::Properties:
        return static_cast<uint32_t>(j_property_id::ALL);
    default:
        return 0;
    }
}
