#include "j_profile_dialog.h"

#include <QCloseEvent>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include "gui/display/j_action_toolbar.h"

j_profile_dialog::j_profile_dialog(QWidget* parent) : QDialog(parent)
{
    cb = new QComboBox(this);
    connect(cb, &QComboBox::activated, this, &j_profile_dialog::configure_editable);
    cb->setFixedHeight(30);
    cb->setFixedWidth(120);
    cb->setEditable(false);
    cb->setDuplicatesEnabled(false);

    tb = new j_action_toolbar("", this);
    tb->setMovable(false);
    tb->setFloatable(false);
    tb->setOrientation(Qt::Vertical);

    QLabel* profiles_cc = new QLabel("Profiles: 0");
    QGridLayout* layout = new QGridLayout();
    layout->setSpacing(10);
    layout->addWidget(tb, 0, 0, 2, 1, Qt::AlignTop);
    layout->addWidget(cb, 0, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(profiles_cc, 1, 1, 1, 1, Qt::AlignRight);
    layout->setContentsMargins(5, 10, 10, 10);

    setLayout(layout);
    setWindowTitle("Select Profile");
}

void j_profile_dialog::exec_profiles(QStringList names, j_profile_dialog_action action)
{
    if (action == j_profile_dialog_action::None)
        return;
    if (!isVisible())
    {
        //tb->add_action(j_toolbar_action_t::A_SELECT, "Select");
        foreach (auto name, names)
            cb->addItem(name);
        if (action == j_profile_dialog_action::SaveNewProfile)
            cb->addItem("new profile");
        current_action = action;
        setFixedSize(baseSize());
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
