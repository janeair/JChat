#ifndef J_PROFILE_DIALOG_H
#define J_PROFILE_DIALOG_H

#include <QDialog>
#include <QComboBox>

class action_toolbar;

enum class j_profile_dialog_action
{
    None,
    GetProfileData,
    SaveNewProfile,
    EditProfiles,
};

class j_profile_dialog : public QDialog
{
    Q_OBJECT

public:
    j_profile_dialog(QWidget* parent = nullptr);
    void exec_profiles(QStringList names, j_profile_dialog_action action = j_profile_dialog_action::None);

protected slots:
    void closeEvent(QCloseEvent* event);
    void select_profile();

signals:
    void selected_profile(j_profile_dialog_action action, QString name);

private:
    j_profile_dialog_action current_action =  j_profile_dialog_action::None;
    action_toolbar* tb = nullptr;
    QComboBox* cb = nullptr;

private slots:
    void configure_editable(int index);
};

#endif // J_PROFILE_DIALOG_H
