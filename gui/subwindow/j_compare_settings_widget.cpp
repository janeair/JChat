#include "j_compare_settings_widget.h"

#include "import/single_weight_data.h"
#include "common/property/j_msg_property.h"

#include <QTableView>
#include <QHeaderView>

QString enum_to_string(j_compare_settings_column_t t)
{
    switch (t)
    {
    case j_compare_settings_column_t::title:
        return QString("Property");
    case j_compare_settings_column_t::weight:
        return QString("Weight");
    default:
        return QString();
    }
}

///######################################################

j_compare_settings_model::j_compare_settings_model(QObject *parent) : QAbstractTableModel(parent)
{

}

int j_compare_settings_model::rowCount(const QModelIndex &) const
{
    return (settings_data) ? settings_data->count() : 0;
}

int j_compare_settings_model::columnCount(const QModelIndex &) const
{
    return static_cast<int>(j_compare_settings_column_t::COUNT);
}

QVariant j_compare_settings_model::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (!settings_data)
        return value;
    switch (role)
    {
    case Qt::DisplayRole:
    {
        auto title = enum_to_string(static_cast<j_property_id>(index.row()));
        switch (index.column())
        {
        case static_cast<int>(j_compare_settings_column_t::title):
        {
            value = title;
        }
        break;
        case static_cast<int>(j_compare_settings_column_t::weight):
        {
            value = settings_data->get_int(title);
        }
        break;
        }
    }
    break;
    case Qt::TextAlignmentRole:
    {
        value = Qt::AlignCenter;
    }
    break;
    }
    return value;
}

QVariant j_compare_settings_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value;
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal && section < static_cast<int>(j_compare_settings_column_t::COUNT))
             value = enum_to_string(static_cast<j_compare_settings_column_t>(section));
        else if (orientation == Qt::Vertical)
             value = QString::number(section + 1);
    }
    return value;
}

bool j_compare_settings_model::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

Qt::ItemFlags j_compare_settings_model::flags(const QModelIndex &index) const
{
    switch (index.column())
    {
    case static_cast<int>(j_compare_settings_column_t::title):
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
    default:
        return Qt::ItemIsEnabled;
    }
}

void j_compare_settings_model::set_data(single_weight_data *data)
{
    if (data)
        settings_data = data;
}

///######################################################

j_compare_settings_widget::j_compare_settings_widget(QWidget *parent) : QDockWidget(parent)
{
    table = new QTableView(this);
    model = new j_compare_settings_model(this);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->setFixedWidth(title_w + weight_w + border_w);

    setWidget(table);
    setWindowTitle("Settings");
}

void j_compare_settings_widget::set_data(single_weight_data *data)
{
    if (data)
    {
        model->set_data(data);
        table->setModel(model);
        table->setColumnWidth(static_cast<int>(j_compare_settings_column_t::title), title_w);
        table->setColumnWidth(static_cast<int>(j_compare_settings_column_t::weight), weight_w);
        int count = model->rowCount(QModelIndex());
        for (auto i = 0; i < count; i++)
            table->setRowHeight(i, row_h);
    }
}
