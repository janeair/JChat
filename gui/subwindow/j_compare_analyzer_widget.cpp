#include "j_compare_analyzer_widget.h"

#include "common/profile/j_profile.h"
#include "gui/common/j_action_toolbar.h"
#include "import/color_dialog_button.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

j_profile_combobox::j_profile_combobox(QWidget *parent) : QComboBox(parent)
{
    setMinimumWidth(100);
    setMaxCount(5);
}

const QString j_profile_combobox::selected_profile() const
{
    return currentText();
}

void j_profile_combobox::set_profile_base(j_profile_base *data)
{
    if (data)
    {
        base = data;
        connect(base, &j_profile_base::profile_count_changed, this, &j_profile_combobox::update_list);
        connect(base, &j_profile_base::profile_name_changed, this, &j_profile_combobox::update_list);
    }
    update_list();
}

void j_profile_combobox::update_list()
{
    auto selected_p = currentText();
    clear();
    if (!base)
        return;
    auto list = base->get_profiles();
    foreach (auto p, list)
        addItem(p->get_name());
    int index = findText(selected_p);
    if (index >= 0)
        setCurrentIndex(index);
    else
        setCurrentIndex(0);
}

///#####################################################

j_compare_analyzer_widget::j_compare_analyzer_widget(QWidget *parent) : QMainWindow(parent)
{
    toolbar = new action_toolbar("Actions", this);
    first_p = new j_profile_combobox(this);
    second_p = new j_profile_combobox(this);
    chart_color_btn = new color_dialog_button(QColor(), this);

    toolbar->add_action<j_compare_analyzer_widget, j_compare_analyzer_widget>
            (icon(j_toolbar_action_t::A_SELECT), "Compare profiles", this, &j_compare_analyzer_widget::add_chart, this, &j_compare_analyzer_widget::chart_can_be_added, false);
    toolbar->add_action<j_compare_analyzer_widget>
            (icon(j_toolbar_action_t::A_DELETE), "Clear charts", this, &j_compare_analyzer_widget::clear_charts);

    connect(first_p, &QComboBox::currentIndexChanged, this, &j_compare_analyzer_widget::selected_profile_changed);
    connect(second_p, &QComboBox::currentIndexChanged, this, &j_compare_analyzer_widget::selected_profile_changed);
    connect(chart_color_btn, &color_dialog_button::color_changed, this, &j_compare_analyzer_widget::selected_profile_changed);

    std::function<QLabel* (const QString &)> create_label ([this] (const QString &title)
    {
        QLabel* label = new QLabel(title, this);
        label->setContentsMargins(5, 0, 5, 0);
        label->setAlignment(Qt::AlignCenter);
        return label;
    });

    QHBoxLayout* p_group = new QHBoxLayout();
    p_group->addWidget(create_label("Compare"));
    p_group->addWidget(first_p);
    p_group->addWidget(create_label("To"));
    p_group->addWidget(second_p);
    p_group->addWidget(create_label("Color"));
    p_group->addWidget(chart_color_btn);
    p_group->addStretch(1);

    QVBoxLayout* main_group = new QVBoxLayout();
    main_group->addLayout(p_group);
    main_group->addStretch(1);
    QWidget* central_scene = new QWidget();
    central_scene->setLayout(main_group);
    setCentralWidget(central_scene);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    setWindowTitle("Compare Analyzer");
}

void j_compare_analyzer_widget::set_profile_base(j_profile_base *data)
{
    if (data)
    {
        first_p->set_profile_base(data);
        second_p->set_profile_base(data);
    }
}

void j_compare_analyzer_widget::add_chart()
{

}

void j_compare_analyzer_widget::clear_charts()
{

}

void j_compare_analyzer_widget::selected_profile_changed()
{
    bool enable = (first_p->currentIndex() >= 0)
            && (second_p->currentIndex() >= 0
            && chart_color_btn->color().isValid())
            && comparator;
    Q_EMIT chart_can_be_added(enable);
}
