#include "gui/log/j_log_action.h"

#include <QString>

QString enum_to_string(j_log_action_t t)
{
    switch(t)
    {
    case j_log_action_t::ANALYZE_MSG:
        return QString("analysing text");
    case j_log_action_t::PROCESS_MSG:
        return QString("processing text");
    case j_log_action_t::SAVE_PROFILE:
        return QString("saving profile");
    case j_log_action_t::OPEN_PROFILE:
        return QString("opening profile");
    case j_log_action_t::IMPORT_DATA:
        return QString("import to");
    case j_log_action_t::EXPORT_DATA:
        return QString("export from");
    default:
        return QString();
    }
}
