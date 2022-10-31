#ifndef J_COMPARE_RES_T_H
#define J_COMPARE_RES_T_H

class QString;
class QColor;

enum class j_compare_res_t
{
    TopMatch,
    MiddleMatch,
    LowMatch,

    COUNT
};

const QString enum_to_string(j_compare_res_t t);
const QColor enum_to_default_color(j_compare_res_t t);

#endif // J_COMPARE_RES_T_H
