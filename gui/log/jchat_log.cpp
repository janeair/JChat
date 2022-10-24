#include "gui/log/jchat_log.h"

#include <QTextEdit>

j_log_widget::j_log_widget(QWidget* parent) : QDockWidget(parent)
{
    text_log = new QTextEdit(this);
    text_log->setReadOnly(true);
    connect(text_log, &QTextEdit::textChanged, [this] () { Q_EMIT log_text_changed(text_log->toPlainText().length() > 0); });
    connect(this, &QDockWidget::dockLocationChanged,
            [this] (Qt::DockWidgetArea area)
    {
        if (area != Qt::NoDockWidgetArea)
            setFixedHeight(60);
        else
            setMaximumHeight(QWIDGETSIZE_MAX);
    });
    setWidget(text_log);
    setWindowTitle("History");
}

void j_log_widget::log_message(j_log_action_t t, QString decr)
{
    text_log->append(enum_to_string(t) + " " + decr);
}

void j_log_widget::clear()
{
    text_log->clear();
}
