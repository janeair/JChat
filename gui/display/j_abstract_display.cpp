#include "j_abstract_display.h"

#include "gui/display/j_display_type.h"
#include "gui/subwindow/text_file_io_dialog.h"
#include "gui/log/j_log_action.h"
#include "import/action_toolbar.h"

#include "common/j_module_t.h"
#include "common/j_stats_t.h"
#include "common/j_compare_res_t.h"
#include "common/ling/j_ling.h"
#include "common/property/j_msg_property.h"
#include "proc/handlers/j_ling_abstract_handler.h"

#include <QGridLayout>
#include <QDockWidget>
#include <QMainWindow>
#include <QTextEdit>

j_settings_model::j_settings_model(j_display_type t, QWidget *parent)
    : settings_tree_model(parent)
{
    tree_settings_item* root;
    switch (t)
    {
    case j_display_type::input:
    {
        root = new tree_settings_item(nullptr, "Modules");
        auto count = static_cast<int>(j_module_t::COUNT);
        for (int i = 0; i < count; i++)
        {
            j_module_t type = static_cast<j_module_t>(i);
            QString name = enum_to_string(type);
            tree_settings_item* top_item = new tree_settings_item(root, name);
            switch (type)
            {
            case j_module_t::Linguist:
                {
                    auto count = static_cast<int>(j_ling_type::All);
                    for (int i = 1; i < count; i = i << 1)
                    {
                        j_ling_type type = static_cast<j_ling_type>(i);
                        QString name = enum_to_string(type);
                        tree_settings_item* item = new tree_settings_item(top_item, name, enum_to_default_color(type));
                        top_item->add_child(item);
                    }
                }
                break;
            case j_module_t::Processor:
                {
                    auto count = static_cast<int>(j_handler_id::AllHandlers) + 1;
                    for (int i = 1; i < count; i = i << 1)
                    {
                        j_handler_id type = static_cast<j_handler_id>(i);
                        QString name = enum_to_string(type);
                        tree_settings_item* item = new tree_settings_item(top_item, name);
                        top_item->add_child(item);
                    }
                }
                break;
            default:
                break;
            }
            root->add_child(top_item);
        }
    }
    break;
    case j_display_type::output:
    {
        root = new tree_settings_item(nullptr, "Stats");
        auto count = static_cast<int>(j_stats_t::COUNT);
        for (int i = 0; i < count; i++)
        {
            j_stats_t type = static_cast<j_stats_t>(i);
            QString name = enum_to_string(type);
            tree_settings_item* top_item = new tree_settings_item(root, name, enum_to_default_color(type));
            switch (type)
            {
            case j_stats_t::property:
            {
                auto count = static_cast<int>(j_property_id::COUNT);
                for (int i = 0; i < count; i++)
                {
                    j_property_id type = static_cast<j_property_id>(i);
                    QString name = enum_to_string(type);
                    tree_settings_item* item = new tree_settings_item(top_item, name);
                    top_item->add_child(item);
                }
            }
            break;
            case j_stats_t::compare:
            {
                auto count = static_cast<int>(j_compare_res_t::COUNT);
                for (int i = 0; i < count; i++)
                {
                    j_compare_res_t type = static_cast<j_compare_res_t>(i);
                    QString name = enum_to_string(type);
                    tree_settings_item* item = new tree_settings_item(top_item, name, enum_to_default_color(type));
                    top_item->add_child(item);
                }
            }
            break;
            default:
            break;
            }
            root->add_child(top_item);
        }
    }
    break;
    }
    create_root(root);
}

j_abstract_display::j_abstract_display(j_display_type t, QWidget *parent)
    : QDockWidget(parent)
{
    tb = new action_toolbar("Actions", this);
    j_settings_model *model = new j_settings_model(t, this);
    stngs = new tree_settings_widget(model);
    fld = new QTextEdit(this);
    connect(fld, &QTextEdit::textChanged, [this] () { Q_EMIT field_text_changed(fld->toPlainText().length() > 0); });
    QDockWidget* field = new QDockWidget("Field");
    field->setWidget(fld);

    QMainWindow* w = new QMainWindow();
    w->addToolBar(tb);
    w->addDockWidget(Qt::LeftDockWidgetArea, stngs);
    stngs->setVisible(false);
    w->addDockWidget(Qt::RightDockWidgetArea, field);
    setWidget(w);

    setWindowTitle(enum_to_string(t));
}

void j_abstract_display::clear_field()
{
    fld->clear();
}

void j_abstract_display::import_to_field()
{
    fld->clear();
    QStringList text = io_dialog::open_text_content(this);
    foreach (auto string, text)
        fld->append(string);
    Q_EMIT log_this(j_log_action_t::IMPORT_DATA, "<" + windowTitle().toLower() + ">");
}

void j_abstract_display::add_word(const QString &text, const QColor &color)
{
    auto _color = color.isValid() ? color : Qt::black;
    field()->setTextColor(_color);
    field()->insertPlainText(text);
}

void j_abstract_display::add_string(const QString &text, const QColor &color)
{
    auto _color = color.isValid() ? color : Qt::black;
    field()->setTextColor(_color);
    field()->append(text);
}

void j_abstract_display::add_tab_string(const QString &text, const QColor &color)
{
    auto _color = color.isValid() ? color : Qt::black;
    field()->setTextColor(_color);
    field()->append("    " + text);
}

void j_abstract_display::add_empty_string()
{
    field()->setTextColor(Qt::black);
    field()->append("");
}

void j_abstract_display::export_from_field()
{
    if (io_dialog::save_text_content(this, fld->toPlainText()))
    {
        fld->clear();
        Q_EMIT log_this(j_log_action_t::EXPORT_DATA, "<" + windowTitle().toLower() + ">");
    }
}
