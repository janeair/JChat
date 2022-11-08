#include "common/property/j_msg_property.h"

const QString enum_to_string(j_property_id id)
{
    switch (id)
    {
    case j_property_id::WORDS_IN_MESSAGE:
        return QString("words in message");
    case j_property_id::SYMBOLS_IN_WORD:
        return QString("symbols in word");
    default:
        return QString();
    }
}

j_simple_property::j_simple_property(const j_simple_property &another) : j_abstract_property(another.id_enum())
{
    set_data(another.data());
}

double j_simple_property::correlation(j_abstract_property *another)
{
    if (another && another->is_simple() && can_be_merged(this, another))
    {
        j_simple_property* s_prop = static_cast<j_simple_property*>(another);
        if (is_empty() || s_prop->is_empty())
            return 0.;
        else
            return 1 - sqrt(abs(value - s_prop->value) / (value + s_prop->value));
    }
    else
        return 0.;
}

bool j_simple_property::join(j_abstract_property *another)
{
    if (another && another->is_simple() && can_be_merged(this, another) && !another->is_empty())
    {
        j_simple_property* s_prop = static_cast<j_simple_property*>(another);
        if (is_empty())
        {
            set_data(s_prop->value);
            set_weight(s_prop->weight());
        }
        else
        {
            uint32_t sum_weight = weight() + s_prop->weight();
            set_data( (value * weight() + s_prop->value * s_prop->weight()) / sum_weight);
            set_weight(sum_weight);
        }
        return true;
    }
    else
        return false;
}
