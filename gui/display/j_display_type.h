#ifndef J_DISPLAY_TYPE_H
#define J_DISPLAY_TYPE_H

class QString;

enum class j_display_type
{
    input,
    output,
};

QString enum_to_string(j_display_type t);

#endif // J_DISPLAY_TYPE_H
