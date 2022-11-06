#ifndef J_INPUT_DISPLAY_H
#define J_INPUT_DISPLAY_H

#include "gui/display/j_abstract_display.h"
#include "common/ling/j_ling.h"
#include "proc/handlers/j_ling_abstract_handler.h"

class j_input_display : public j_abstract_display
{
    Q_OBJECT

public:
    j_input_display(QWidget* parent = nullptr);
    j_ling_types get_ling_settings() const;
    j_handlers get_proc_settings() const;
    bool get_comp_settings() const;
    const settings_item* get_ling_settings_data() const;

public slots:
    void rewrite_input_message(QList<j_ling> list);

signals:
    void to_configure(uint32_t msgs);
    void to_analyse(const QString& msg);

private slots:
    void process_input();

private:
};

#endif // J_INPUT_DISPLAY_H
