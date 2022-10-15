#include "gui/dialog/text_file_io_dialog.h"

#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>

bool io_dialog::save_text_content(QWidget* parent, QString content)
{
    QString file_name = QFileDialog::getSaveFileName(parent, "Save content to", QDir::currentPath(), "Text files (*.txt)");
    QFile save_file(file_name);
    if (!save_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&save_file);
    out << content;
    save_file.close();
    return true;
}

QStringList io_dialog::open_text_content(QWidget* parent)
{
    QStringList open_text_list;
    QStringList open_files_list = QFileDialog::getOpenFileNames(parent, "Open content from", QDir::currentPath(), "Text files (*.txt)");
    foreach (auto file_name, open_files_list)
    {
        QFile open_file(file_name);
        if (!open_file.open(QIODevice::ReadOnly | QIODevice::Text))
            break;
        QTextStream in(&open_file);
        open_text_list.append(in.readAll());
        open_file.close();
    }
    return open_text_list;
}
