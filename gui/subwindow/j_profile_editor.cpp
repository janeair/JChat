#include "gui/subwindow/j_profile_editor.h"

#include <QCloseEvent>
#include <QVBoxLayout>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>

#include "gui/common/j_action_toolbar.h"

j_profile_editor_table_model::j_profile_editor_table_model(QObject* parent) : QAbstractTableModel(parent)
{

}

j_profile_editor::j_profile_editor(QWidget* parent) : QMainWindow(parent)
{
    toolbar = new action_toolbar("", this);
    //toolbar->setMovable(false);
    toolbar->setFloatable(false);

    current_profile = new QLineEdit(this);

    profile_table = new QTableView(this);
    //table_model = new j_profile_editor_table_model();

    profiles_cc = new QLabel("Profiles: 0");
    profiles_cc->setAlignment(Qt::AlignRight);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(current_profile);
    layout->addWidget(profile_table);
    layout->addWidget(profiles_cc);
    QWidget* central_scene = new QWidget();
    central_scene->setLayout(layout);
    setCentralWidget(central_scene);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    setWindowTitle("Profile Editor");
}

void j_profile_editor::closeEvent(QCloseEvent* event)
{
    event->accept();
}
