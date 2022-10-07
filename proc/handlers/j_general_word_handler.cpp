#include "j_general_word_handler.h"
#include "common/j_msg_property.h"
#include "common/j_msgs_property_stats.h"

#include <QDebug>

j_general_word_handler::j_general_word_handler(QObject* parent)
    : j_ling_abstract_handler(j_handler_id::GWHandler, j_lang::Rus | j_lang::Eng, j_ling_type::Word, parent)
{

}

void j_general_word_handler::process_msg(QList<j_ling> msg)
{
    work(); /// start processing

    /// counting stats
    int words_count = 0;
    int symbols_count = 0;
    for (QList<j_ling>::const_iterator i = msg.cbegin(); i != msg.cend(); ++i)
    {
        if (types().testFlag((*i).type) && langs().testFlag((*i).lang))
        {
            words_count++;
            symbols_count += (*i).str.length();
        }
    }

    /// creating properties
    j_simple_property* w_in_msg = new j_simple_property(j_property_id::WORDS_IN_MESSAGE);
    w_in_msg->set_data(words_count);
    w_in_msg->set_weight(1);
    j_simple_property* s_in_w = new j_simple_property(j_property_id::SYMBOLS_IN_WORD);
    double avg_s = (words_count == 0) ? 0. : (double)symbols_count / words_count;
    s_in_w->set_data(avg_s);
    s_in_w->set_weight(words_count);

    /// creating stats
    j_msgs_property_stats data;
    data.append(w_in_msg);
    data.append(s_in_w);

    work(); /// end processing

    emit stats_ready(std::move(data));
}
