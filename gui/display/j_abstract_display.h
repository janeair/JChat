#ifndef J_ABSTRACT_DISPLAY_H
#define J_ABSTRACT_DISPLAY_H

#include <QDockWidget>

class j_settings;
class j_settings_widget;
class action_toolbar;
class QTextEdit;

class j_abstract_display : public QDockWidget
{
    Q_OBJECT

public:
    explicit j_abstract_display(QString title, j_settings st, QWidget *parent = nullptr);
    ~j_abstract_display() = default;

    action_toolbar* toolbar() { return tb; }
    j_settings_widget* settings_widget() { return stngs; }
    QTextEdit* field() { return fld; }

signals:
    void field_text_changed(bool is_clear);

private:
    action_toolbar* tb = nullptr;
    j_settings_widget* stngs = nullptr;
    QTextEdit* fld = nullptr;
};

#endif // J_ABSTRACT_DISPLAY_H
