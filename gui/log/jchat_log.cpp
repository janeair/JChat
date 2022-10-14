#include "gui/log/jchat_log.h"

#include <QTextEdit>

j_log_widget::j_log_widget(QWidget* parent) : QDockWidget(parent)
{
    text_log = new QTextEdit(this);
    text_log->setFixedHeight(40);
    text_log->setReadOnly(true);
    connect(text_log, &QTextEdit::textChanged, [this] () { emit log_text_changed(text_log->toPlainText().length() > 0); });

    setWidget(text_log);
    setWindowTitle("History");
}

void j_log_widget::log_message(j_log_action_t t, QString decr)
{
    text_log->append("> " + enum_to_string(t) + ": " + decr);
}

void j_log_widget::clear()
{
    text_log->clear();
}
