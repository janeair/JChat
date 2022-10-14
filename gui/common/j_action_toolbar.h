#ifndef J_ACTION_TOOLBAR_H
#define J_ACTION_TOOLBAR_H

#include "import/action_toolbar.h"

class QIcon;

enum class j_toolbar_action_t
{
    A_SELECT,
    A_DELETE,
    A_EDIT,
    A_SAVE,
    A_OPEN,
    A_IMPORT,
    A_EXPORT,
    A_SETTINGS,
    A_PROFILE,
    A_ADD_PROFILE,
    A_EDIT_PROFILE,

    COUNT,
};

QString enum_to_string(j_toolbar_action_t t);
QString enum_to_icon_path(j_toolbar_action_t t);
QIcon icon(j_toolbar_action_t t);

#endif // J_ACTION_TOOLBAR_H
