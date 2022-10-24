#ifndef J_LOG_ACTION_H
#define J_LOG_ACTION_H

class QString;

enum class j_log_action_t
{
    ANALYZE_MSG,
    PROCESS_MSG,
    COMPARE_MSG,

    SAVE_PROFILE,
    OPEN_PROFILE,
    DELETE_PROFILE,
    RENAME_PROFILE,

    IMPORT_DATA,
    EXPORT_DATA,

    COUNT
};

QString enum_to_string(j_log_action_t t);

#endif // J_LOG_ACTION_H
