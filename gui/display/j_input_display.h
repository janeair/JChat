#ifndef J_INPUT_DISPLAY_H
#define J_INPUT_DISPLAY_H

#include "gui/display/j_abstract_display.h"
#include "common/j_settings.h"

class j_input_display : public j_abstract_display
{
    Q_OBJECT

public:
    j_input_display(QWidget* parent = nullptr);

signals:
    void to_configure(uint32_t msgs, j_settings st);
    void to_analyse(const QString& msg);

private slots:
    void process_input();

private:
};

#endif // J_INPUT_DISPLAY_H
