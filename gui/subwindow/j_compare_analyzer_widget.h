#ifndef J_COMPARE_ANALYZER_WIDGET_H
#define J_COMPARE_ANALYZER_WIDGET_H

#include <QMainWindow>
#include <QComboBox>

class j_profile_base;
class action_toolbar;
class j_comparator;
class color_dialog_button;
class j_compare_settings_widget;

class j_profile_combobox : public QComboBox
{
    Q_OBJECT

public:
    j_profile_combobox(QWidget* parent = nullptr);
    const QString selected_profile() const;
    void set_profile_base(j_profile_base* data);

private:
    j_profile_base* base = nullptr;

private slots:
    void update_list();
};

class j_compare_analyzer_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit j_compare_analyzer_widget(QWidget *parent = nullptr);
    void set_comparator(j_comparator* comp);

public slots:
    void set_profile_base(j_profile_base* data);
    void add_chart();
    void clear_charts();
    void selected_profile_changed();

signals:
    void chart_can_be_added(bool enable);

private:
    action_toolbar* toolbar = nullptr;
    j_profile_combobox* first_p = nullptr;
    j_profile_combobox* second_p = nullptr;
    j_compare_settings_widget* settings = nullptr;
    color_dialog_button* chart_color_btn = nullptr;

    j_comparator* comparator = nullptr;

};

#endif // J_COMPARE_ANALYZER_WIDGET_H
