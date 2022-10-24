#include "j_abstract_display.h"

#include "gui/display/settings/j_settings.h"
#include "gui/subwindow/text_file_io_dialog.h"
#include "gui/log/j_log_action.h"
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
    connect(fld, &QTextEdit::textChanged, [this] () { Q_EMIT field_text_changed(fld->toPlainText().length() > 0); });
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

void j_abstract_display::import_to_field()
{
    fld->clear();
    QStringList text = io_dialog::open_text_content(this);
    foreach (auto string, text)
        fld->append(string);
    Q_EMIT log_this(j_log_action_t::IMPORT_DATA, "<" + windowTitle().toLower() + ">");
}

void j_abstract_display::export_from_field()
{
    if (io_dialog::save_text_content(this, fld->toPlainText()))
    {
        fld->clear();
        Q_EMIT log_this(j_log_action_t::EXPORT_DATA, "<" + windowTitle().toLower() + ">");
    }
}
