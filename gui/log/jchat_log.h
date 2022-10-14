#ifndef JCHAT_LOG_H
#define JCHAT_LOG_H

#include "gui/log/j_log_action.h"

#include <QDockWidget>

class QTextEdit;

class j_log_widget : public QDockWidget
{
    Q_OBJECT

public:
    j_log_widget(QWidget* parent = nullptr);
    QTextEdit* log_widget() const { return text_log; }

signals:
    void log_text_changed(bool is_clear);

public slots:
    void log_message(j_log_action_t t, QString decr = "");
    void clear();

private:
    QTextEdit* text_log = nullptr;

};

#endif // JCHAT_LOG_H
