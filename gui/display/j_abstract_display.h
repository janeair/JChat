#ifndef J_ABSTRACT_DISPLAY_H
#define J_ABSTRACT_DISPLAY_H

#include <QDockWidget>

class j_settings;
class j_settings_widget;
class action_toolbar;
class QTextEdit;

enum class j_log_action_t;
enum class j_display_type;

class j_abstract_display : public QDockWidget
{
    Q_OBJECT

public:
    explicit j_abstract_display(j_display_type t, QWidget *parent = nullptr);
    ~j_abstract_display() = default;

    action_toolbar* toolbar() { return tb; }
    j_settings_widget* settings_widget() { return stngs; }
    QTextEdit* field() { return fld; }

public slots:
    void export_from_field();
    void import_to_field();

signals:
    void field_text_changed(bool is_clear);
    void log_this(j_log_action_t t, QString decr);

private:
    action_toolbar* tb = nullptr;
    j_settings_widget* stngs = nullptr;
    QTextEdit* fld = nullptr;
};

#endif // J_ABSTRACT_DISPLAY_H
