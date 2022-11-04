#ifndef J_COMPARE_RES_T_H
#define J_COMPARE_RES_T_H

class QString;
class QColor;

enum class j_compare_res_t
{
    TopMatch,           // >80%
    MiddleMatch,        // 50%-80%
    LowMatch,           // <50%

    COUNT
};

const QString enum_to_string(j_compare_res_t t);
const QColor enum_to_default_color(j_compare_res_t t);
j_compare_res_t compare_res_t_from_value(double value);

#endif // J_COMPARE_RES_T_H
