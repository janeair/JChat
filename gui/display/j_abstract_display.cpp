#include "j_abstract_display.h"

#include "common/j_settings.h"

#include <QGridLayout>
#include <QDockWidget>
#include <QMainWindow>
#include <QTextEdit>

j_abstract_display::j_abstract_display(QString title, j_settings st, QWidget *parent)
    : QDockWidget(parent)
{
    tb = new j_action_toolbar("Actions", this);
    stngs = new j_settings_widget(st, this);
    fld = new QTextEdit(this);
    QDockWidget* field = new QDockWidget("Field");
    field->setWidget(fld);

    connect(tb, &j_action_toolbar::to_delete, fld, &QTextEdit::clear);
    connect(tb, &j_action_toolbar::to_settings,
            [this] ()
    {
        if (stngs->isHidden())
            stngs->show();
        else
            stngs->hide();
    });
    connect(fld, &QTextEdit::textChanged,
            [this] ()
    {
        bool val = (fld->toPlainText().length() > 0);
        tb->set_enabled(j_toolbar_action_t::A_DELETE, val);
        tb->set_enabled(j_toolbar_action_t::A_EXPORT, val);
        tb->set_enabled(j_toolbar_action_t::A_SELECT, val);
    });

    QMainWindow* w = new QMainWindow();
    w->addToolBar(tb);
    w->addDockWidget(Qt::LeftDockWidgetArea, stngs);
    stngs->setVisible(false);
    w->addDockWidget(Qt::RightDockWidgetArea, field);
    setWidget(w);
    setWindowTitle(title);
}
