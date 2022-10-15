#pragma once

#include <QString>

class QWidget;

namespace io_dialog
{
    bool save_text_content(QWidget* parent, QString content = QString());
    QStringList open_text_content(QWidget* parent);
}
