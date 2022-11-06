#ifndef J_ABSTRACT_DISPLAY_H
#define J_ABSTRACT_DISPLAY_H

#include "import/settings_widget.h"
#include <QDockWidget>

using namespace tree_settings;

class action_toolbar;
class QTextEdit;

enum class j_log_action_t;
enum class j_display_type;

class j_settings_model : public settings_tree_model
{
public:
    j_settings_model(j_display_type t, QWidget* parent = nullptr);
};

class j_abstract_display : public QDockWidget
{
    Q_OBJECT

public:
    explicit j_abstract_display(j_display_type t, QWidget *parent = nullptr);
    ~j_abstract_display() = default;

    const action_toolbar* toolbar() const { return tb; }
    action_toolbar* toolbar() { return tb; }
    const settings_widget* settings() const { return stngs; }
    settings_widget* settings() { return stngs; }
    const QTextEdit* field() const { return fld; }
    QTextEdit* field() { return fld; }

    void clear_field();

public slots:
    void export_from_field();
    void import_to_field();

signals:
    void field_text_changed(bool is_clear);
    void log_this(j_log_action_t t, QString decr);

protected:
    void add_word(const QString &text, const QColor &color);
    void add_string(const QString &text, const QColor &color);
    void add_tab_string(const QString &text, const QColor &color);
    void add_empty_string();

private:
    action_toolbar *tb = nullptr;
    settings_widget *stngs = nullptr;
    QTextEdit *fld = nullptr;
};

#endif // J_ABSTRACT_DISPLAY_H
