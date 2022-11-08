#ifndef J_COMPARE_SETTINGS_WIDGET_H
#define J_COMPARE_SETTINGS_WIDGET_H

#include <QDockWidget>
#include <QAbstractTableModel>

class QTableView;
class single_weight_data;

enum class j_compare_settings_column_t
{
    title,
    weight,

    COUNT
};

QString enum_to_string(j_compare_settings_column_t t);

class j_compare_settings_model : public QAbstractTableModel
{
public:
    j_compare_settings_model(QObject* parent = nullptr);
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex&index) const override;

    void set_data(single_weight_data* data);

private:
    single_weight_data* settings_data = nullptr;
};

class j_compare_settings_widget : public QDockWidget
{
    Q_OBJECT

public:
    explicit j_compare_settings_widget(QWidget* parent = nullptr);
    void set_data(single_weight_data* data);

private:
    QTableView* table = nullptr;
    j_compare_settings_model* model = nullptr;

    const int title_w = 120;
    const int weight_w = 50;
    const int border_w = 15;
    const int row_h = 20;
};

#endif // J_COMPARE_SETTINGS_WIDGET_H
