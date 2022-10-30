#include "j_display_type.h"

#include <QString>

QString enum_to_string(j_display_type t)
{
    switch (t)
    {
    case j_display_type::input:
        return QString("Input");
    case j_display_type::output:
        return QString("Output");
    }
}
