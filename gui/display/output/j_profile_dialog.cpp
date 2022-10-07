#include "j_profile_dialog.h"

#include <QCloseEvent>
#include <QHBoxLayout>
#include <QPushButton>

j_profile_dialog::j_profile_dialog(QWidget* parent) : QDialog(parent)
{
    cb = new QComboBox(this);
    connect(cb, &QComboBox::activated, this, &j_profile_dialog::configure_editable);
    cb->setEditable(false);
    cb->setDuplicatesEnabled(false);

    QPushButton* select = new QPushButton(QIcon(":/icons/resources/check_all_icon.ico"), "", this);
    connect(select, &QPushButton::pressed, this, &j_profile_dialog::select_profile);
    select->setToolTip("Select");

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(select, 0);
    layout->addWidget(cb, 1);

    setLayout(layout);
    setMinimumSize(QSize(150, 50));
    setFixedHeight(50);
    setWindowTitle("Select Profile");
}

void j_profile_dialog::exec_profiles(QStringList names, j_profile_dialog_action action)
{
    if (action == j_profile_dialog_action::None)
        return;
    if (!isVisible())
    {
        foreach (auto name, names)
            cb->addItem(name);
        if (action == j_profile_dialog_action::SaveNewProfile)
            cb->addItem("new profile");
        current_action = action;
        exec();
    }
}

void j_profile_dialog::closeEvent(QCloseEvent* event)
{
    cb->clear();
    cb->setEditable(false);
    current_action = j_profile_dialog_action::None;
    event->accept();
}

void j_profile_dialog::select_profile()
{
    emit selected_profile(current_action, cb->currentText());
    close();
}

void j_profile_dialog::configure_editable(int index)
{
    if (index == cb->count() - 1 && current_action == j_profile_dialog_action::SaveNewProfile)
        cb->setEditable(true);
    else
        cb->setEditable(false);
}
