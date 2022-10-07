#include "jchat_log.h"

#include <QTextEdit>

j_log_widget::j_log_widget(QWidget* parent) : QDockWidget(parent)
{
    text_log = new QTextEdit(this);
    text_log->setFixedHeight(40);
    text_log->setReadOnly(true);

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

QString enum_to_string(j_log_action_t t)
{
    switch(t)
    {
    case j_log_action_t::ANALYZE_MSG:
        return QString("analysing text");
    case j_log_action_t::PROCESS_MSG:
        return QString("processing text");
    case j_log_action_t::SAVE_PROFILE:
        return QString("saving profile");
    case j_log_action_t::OPEN_PROFILE:
        return QString("opening profile");
    default:
        return QString();
    }
}
