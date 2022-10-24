#include "gui/log/j_log_action.h"

#include <QString>

QString enum_to_string(j_log_action_t t)
{
    switch(t)
    {
    case j_log_action_t::ANALYZE_MSG:
        return QString("<analyse text>");
    case j_log_action_t::PROCESS_MSG:
        return QString("<process text>");
    case j_log_action_t::COMPARE_MSG:
        return QString("<compare text>");
    case j_log_action_t::SAVE_PROFILE:
        return QString("<save profile> name:" );
    case j_log_action_t::OPEN_PROFILE:
        return QString("<open profile> name:");
    case j_log_action_t::DELETE_PROFILE:
        return QString("<delete profile> name:");
    case j_log_action_t::RENAME_PROFILE:
        return QString("<rename profile>");
    case j_log_action_t::IMPORT_DATA:
        return QString("<import> to:");
    case j_log_action_t::EXPORT_DATA:
        return QString("<export> from:");
    default:
        return QString();
    }
}
