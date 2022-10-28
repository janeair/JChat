#include "gui/subwindow/j_profile_editor.h"

#include <QCloseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QLineEdit>
#include <QLabel>

#include "import/color_dialog_button.h"
#include "gui/common/j_action_toolbar.h"
#include "common/profile/j_profile.h"


QString enum_to_string(j_profile_editor_table_column_t t)
{
    switch (t)
    {
    case j_profile_editor_table_column_t::profile_name:
        return QString("Profile");
    case j_profile_editor_table_column_t::profile_type:
        return QString("Type");
    case j_profile_editor_table_column_t::profile_properties:
        return QString("Properties");
    default:
        return QString();
    }
}

///######################################################################

j_profile_editor_table_model::j_profile_editor_table_model(const int max_name_size, QObject* parent)
    : QAbstractTableModel(parent), name_size(max_name_size)
{
}

int j_profile_editor_table_model::rowCount(const QModelIndex &) const
{
    if (base)
        return base->count();
    else
        return 0;
}

int j_profile_editor_table_model::columnCount(const QModelIndex &) const
{
    return static_cast<int>(j_profile_editor_table_column_t::COUNT);
}

QVariant j_profile_editor_table_model::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (!base)
        return value;
    switch(role)
    {
        case Qt::DisplayRole:
        {
            auto p = base->get_profile(index.row());
            if (!p)
                return value;
            switch (index.column())
            {
            case static_cast<int>(j_profile_editor_table_column_t::profile_name):
            {
                value = p->get_name();
            }
            break;
            case static_cast<int>(j_profile_editor_table_column_t::profile_type):
            {
                value = enum_to_string(p->get_type());
            }
            break;
            case static_cast<int>(j_profile_editor_table_column_t::profile_properties):
            {
                value = QString::number(p->get_property_count());
            }
            break;
            }
        }
        break;
        case Qt::TextAlignmentRole:
        {
            value = (static_cast<j_profile_editor_table_column_t>(index.column()) == j_profile_editor_table_column_t::profile_name)
                    ? Qt::AlignVCenter : Qt::AlignCenter;
        }
        break;
        case Qt::ForegroundRole:
        {
            value = (index.column() == static_cast<int>(j_profile_editor_table_column_t::profile_type)) ?
                        QBrush(enum_to_color(base->get_profile(index.row())->get_type())) : QBrush(Qt::black);
        }
        break;
        case Qt::ToolTipRole:
        {
            value = (index.column() == static_cast<int>(j_profile_editor_table_column_t::profile_type)) ?
                        enum_to_help_string(base->get_profile(index.row())->get_type()) : QVariant();
        }
        break;
    }
    return value;
}

QVariant j_profile_editor_table_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant value;
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal && section < static_cast<int>(j_profile_editor_table_column_t::COUNT))
             value = enum_to_string(static_cast<j_profile_editor_table_column_t>(section));
        else if (orientation == Qt::Vertical)
             value = QString::number(section + 1);
    }
    return value;
}

bool j_profile_editor_table_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole
            && index.column() != static_cast<int>(j_profile_editor_table_column_t::profile_name)
            && names_can_be_editable)
        return false;
    auto new_name = value.toString();
    if (new_name.isEmpty())
        return false;
    if (new_name.size() > name_size)
        new_name = new_name.first(name_size);
    auto old_name = base->get_profile(index.row())->get_name();
    if (QString::compare(old_name, new_name, Qt::CaseInsensitive) == 0)
        return false;
    bool renamed = base->rename_profile(old_name, new_name);
    Q_EMIT dataChanged(index, index);
    if (renamed)
        Q_EMIT log_this(j_log_action_t::RENAME_PROFILE, "from " + old_name + " to " + new_name);
    return renamed;
}

Qt::ItemFlags j_profile_editor_table_model::flags(const QModelIndex &index) const
{
    switch (index.column())
    {
    case static_cast<int>(j_profile_editor_table_column_t::profile_name):
        return (names_can_be_editable) ? Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled
                                       : Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    default:
        return Qt::ItemIsEnabled;
    }
}

void j_profile_editor_table_model::set_names_editable(bool edit)
{
    names_can_be_editable = edit;
}

bool j_profile_editor_table_model::is_profile_in_base(const QString &p_name)
{
    return (base && base->get_profile(p_name) != nullptr);
}

bool j_profile_editor_table_model::delete_profile(const QString &p_name)
{
    int row = base->index(p_name);
    if (row >= 0)
    {
        int row_end = base->count() - 1;
        beginRemoveRows(QModelIndex(), row, row);
        bool deleted = base->delete_profile(p_name);
        endRemoveRows();
        Q_EMIT dataChanged(index(row_end, 0), index(row_end, static_cast<int>(j_profile_editor_table_column_t::COUNT) - 1));
        Q_EMIT log_this(j_log_action_t::DELETE_PROFILE, p_name);
        return deleted;
    }
    return false;
}

void j_profile_editor_table_model::add_data(const QString &p_name, j_msgs_property_stats data)
{
    int row_p = base->index(p_name);
    if (row_p < 0)
    {
        int row = base->count();
        auto new_name = (p_name.size() > name_size) ? p_name.first(name_size) : p_name;
        beginInsertRows(QModelIndex(), row, row);
        base->add_data(new_name, data);
        endInsertRows();
        Q_EMIT dataChanged(index(row, 0), index(row, static_cast<int>(j_profile_editor_table_column_t::COUNT) - 1));
    }
    else
    {
        base->add_data(p_name, data);
        Q_EMIT dataChanged(index(row_p, 0), index(row_p, static_cast<int>(j_profile_editor_table_column_t::COUNT) - 1));
    }
    Q_EMIT log_this(j_log_action_t::SAVE_PROFILE, p_name);
}

void j_profile_editor_table_model::set_profile_base(j_profile_base *p_base)
{
    base = p_base;
}

///######################################################################

j_profile_editor::j_profile_editor(QWidget* parent) : QMainWindow(parent)
{
    toolbar = new action_toolbar("Actions", this);
    toolbar->setFloatable(false);
    toolbar->add_action<j_profile_editor, j_profile_editor>
            (icon(j_toolbar_action_t::A_SAVE), "Save data to selected profile",
             this, &j_profile_editor::save_to_selected_profile, this, &j_profile_editor::current_stats_changed, false);
    toolbar->add_action<j_profile_editor, j_profile_editor>
            (icon(j_toolbar_action_t::A_OPEN), "Open selected profile",
             this, &j_profile_editor::open_selected_profile, this, &j_profile_editor::selected_profile_changed, false);
    toolbar->add_action<j_profile_editor>
            (icon(j_toolbar_action_t::A_EDIT), "Edit profiles", this, &j_profile_editor::set_edit_profile_names);
    toolbar->add_action<j_profile_editor, j_profile_editor>
            (icon(j_toolbar_action_t::A_DELETE), "Delete selected profile",
             this, &j_profile_editor::delete_selected_profile, this, &j_profile_editor::selected_profile_changed, false);

    current_profile = new QLineEdit(this);
    current_profile->setPlaceholderText("new profile");
    current_profile->setMinimumWidth(100);
    current_profile->setFixedHeight(25);
    current_profile->setMaxLength(max_profile_name_size);
    connect(current_profile, &QLineEdit::textChanged, this, &j_profile_editor::set_selected_profile_color);

    auto in_color_button = new color_dialog_button(in_base_color, this);
    auto out_color_button = new color_dialog_button(out_base_color, this);
    auto in_label = new QLabel("In", this);
    in_label->setMinimumWidth(30);
    in_label->setAlignment(Qt::AlignCenter);
    in_label->setToolTip("Color if selected profile in base");
    auto out_label = new QLabel("Out", this);
    out_label->setMinimumWidth(30);
    out_label->setAlignment(Qt::AlignCenter);
    out_label->setToolTip("Color if selected profile out of base");
    connect(in_color_button, &color_dialog_button::color_changed,
            [this] (QColor color)
    {
        in_base_color = color;
        set_selected_profile_color(current_profile->text());
    });
    connect(out_color_button, &color_dialog_button::color_changed,
            [this] (QColor color)
    {
        out_base_color = color;
        set_selected_profile_color(current_profile->text());
    });

    QHBoxLayout* slc_group = new QHBoxLayout();
    slc_group->addWidget(current_profile);
    slc_group->addStretch(1);
    slc_group->addWidget(in_label);
    slc_group->addWidget(in_color_button);
    slc_group->addWidget(out_label);
    slc_group->addWidget(out_color_button);

    profile_table = new QTableView(this);
    table_model = new j_profile_editor_table_model(max_profile_name_size);
    profile_table->setModel(table_model);
    profile_table->horizontalHeader()->setStretchLastSection(true);
    profile_table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    profile_table->setColumnWidth(static_cast<int>(j_profile_editor_table_column_t::profile_name), 100);
    profile_table->setColumnWidth(static_cast<int>(j_profile_editor_table_column_t::profile_type), 50);

    QItemSelectionModel* slc_model = new QItemSelectionModel(table_model);
    profile_table->setSelectionModel(slc_model);
    connect(slc_model, &QItemSelectionModel::currentChanged, [this] (const QModelIndex &current, const QModelIndex &previous)
    {
        bool is_p_name = current.column() == static_cast<int>(j_profile_editor_table_column_t::profile_name);
        if (is_p_name)
        {
            auto p_name = table_model->data(current, Qt::DisplayRole).toString();
            if ((QString::compare(current_profile->text(), p_name, Qt::CaseInsensitive) != 0))
                current_profile->setText(p_name);
        }
    });

    profiles_cc = new QLabel("Profiles: 0");
    profiles_cc->setAlignment(Qt::AlignRight);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(slc_group);
    layout->addWidget(profile_table);
    layout->addWidget(profiles_cc);
    QWidget* central_scene = new QWidget();
    central_scene->setLayout(layout);
    setCentralWidget(central_scene);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    setWindowTitle("Profile Editor");
}

void j_profile_editor::set_profile_base(j_profile_base *base)
{
    if (!base)
        return;
    connect(base, &j_profile_base::profile_count_changed,
            [this] (int count)
    {
        profiles_cc->setText("Profiles: " + QString::number(count));
    });
    if (table_model)
        table_model->set_profile_base(base);
}

void j_profile_editor::delete_selected_profile()
{
    bool deleted = table_model->delete_profile(current_profile->text());
    if (deleted)
        current_profile->clear();
}

void j_profile_editor::open_selected_profile()
{
    const auto p = table_model->get_base()->get_profile(current_profile->text());
    if (p)
        Q_EMIT profile_to_display(p);
}

void j_profile_editor::set_edit_profile_names(bool edit)
{
    table_model->set_names_editable(edit);
}

void j_profile_editor::save_to_selected_profile()
{
    const auto p_name = current_profile->text();
    if (!p_name.isEmpty())
    {
        table_model->add_data(p_name, current_stats);
        current_profile->clear();
        clear_current_stats();
        profile_table->setRowHeight(table_model->rowCount(QModelIndex()) - 1, 25);
    }
}

void j_profile_editor::set_current_stats(j_msgs_property_stats stats)
{
    current_stats.clear();
    current_stats = std::move(stats);
    Q_EMIT current_stats_changed(!current_stats.is_clear());
}

void j_profile_editor::clear_current_stats()
{
    current_stats.clear();
    Q_EMIT current_stats_changed(!current_stats.is_clear());
}

void j_profile_editor::closeEvent(QCloseEvent* event)
{
    event->accept();
}

void j_profile_editor::set_selected_profile_color(const QString &text)
{
    bool exist = table_model->is_profile_in_base(text);
    bool highlighted = !current_profile->text().isEmpty() && !exist;
    if (highlighted)
    {
        QPalette pal = current_profile->palette();
        pal.setColor(QPalette::Text, out_base_color);
        current_profile->setPalette(pal);
    }
    else
    {
        QPalette pal = current_profile->palette();
        pal.setColor(QPalette::Text, in_base_color);
        current_profile->setPalette(pal);
    }
    Q_EMIT selected_profile_changed(exist);
}
