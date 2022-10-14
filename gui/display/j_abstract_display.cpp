#include "j_abstract_display.h"

#include "gui/display/settings/j_settings.h"
#include "import/action_toolbar.h"

#include <QGridLayout>
#include <QDockWidget>
#include <QMainWindow>
#include <QTextEdit>

j_abstract_display::j_abstract_display(QString title, j_settings st, QWidget *parent)
    : QDockWidget(parent)
{
    tb = new action_toolbar("Actions", this);
    stngs = new j_settings_widget(st, this);
    fld = new QTextEdit(this);
    connect(fld, &QTextEdit::textChanged, [this] () { emit field_text_changed(fld->toPlainText().length() > 0); });
    QDockWidget* field = new QDockWidget("Field");
    field->setWidget(fld);

    QMainWindow* w = new QMainWindow();
    w->addToolBar(tb);
    w->addDockWidget(Qt::LeftDockWidgetArea, stngs);
    stngs->setVisible(false);
    w->addDockWidget(Qt::RightDockWidgetArea, field);
    setWidget(w);

    setWindowTitle(title);
}
