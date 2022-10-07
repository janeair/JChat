#include "j_linguist.h"

#include <QDebug>

j_linguist::j_linguist(QObject *parent) : QObject(parent)
{
    ling_stats = new j_msgs_general_stats();
}

void j_linguist::configure_settings(uint32_t msgs, j_ling_types t)
{
    qDebug() << "linguist: configure settings" << msgs << t;
    assert(msgs > 0);
    msgs_to_proc = msgs;
    types = t;
    is_configured = true;
}

void j_linguist::process_msg(QString text)
{
    if (!is_configured)
        return;
    /// output ling list
    QList<j_ling> lings_out;

    /// actual info while message parsing
    int32_t msg_len = text.length();
    j_ling_type ling_t = char_category(text[0]);
    j_lang lang = char_language(text[0]);
    int32_t ling_start = (j_ling::can_be_multiple_char(ling_t) == j_ling_char_t::Single) ? -1 : 0;

    if (msg_len > 1)
    {
    /// char by char message parsing
    for (int32_t i = 1; i < msg_len; ++i)
    {
        const QChar curr = text[i];
        j_ling_type char_t = char_category(curr);

        if (char_t != ling_t)    /// new ling start
        {
            if (types.testFlag(ling_t))
            {
                if ( ling_start >= 0 )
                    /// append previous multi-char ling
                    lings_out.append(j_ling(ling_t, lang, text.mid(ling_start, i - ling_start)));
                else if ( ling_start < 0 && i != 0)
                    /// append previous single-char ling
                    lings_out.append(j_ling(ling_t, lang, QString(text[i-1])));
            }
            /// set the new ling start
            ling_start = i;
        }
        else                     /// current ling tail
        {
            j_ling_char_t single_or_multi = j_ling::can_be_multiple_char(char_t);

            switch(single_or_multi)
            {
            case j_ling_char_t::Single:
            {
                ling_start = -1;
            }
            break;
            case j_ling_char_t::MultipleIfSame:
            {
                ling_start = (curr == text[i-1]) ? ling_start : i;
            }
            break;
            case j_ling_char_t::Multiple:
            {
                /// leave the same
            }
            break;
            }
        }

        ling_t = char_t;
        lang = ling_language(ling_start == i, lang, curr);
    }

    /// append last ling
    if (types.testFlag(ling_t))
    {
        if ( ling_start >= 0 )
            /// append last multi-char ling
            lings_out.append(j_ling(ling_t, lang, text.mid(ling_start, msg_len - ling_start)));
        else
            /// append last single-char ling
            lings_out.append(j_ling(ling_t, lang, QString(text[msg_len - 1])));
    }
    }

    /// output stats configure
    ling_list.append(lings_out);

    uint lings_cc = lings_out.size();
    j_msgs_general_stats gen_stats;
    for (QList<j_ling>::const_iterator i = lings_out.cbegin();
         i != lings_out.cend(); ++i)
    {
        gen_stats.add_data(j_msgs_general_stats::from_ling_t((*i).type), 1);
    }
    gen_stats.set_data(j_msgs_general_stats_t::Messages, 1);
    gen_stats.set_data(j_msgs_general_stats_t::Lings, lings_cc);

    ling_stats->join(&gen_stats, j_stats_join_t::Merge);

    msgs_ready++;
    if (!is_busy())
    {
        emit lings_to_gui(std::move(ling_list));
        emit stats_to_gui(std::move(*ling_stats));
        clear();
    }

    emit to_process(std::move(lings_out));
}

bool j_linguist::is_busy() const
{
    return (msgs_ready < msgs_to_proc);
}

void j_linguist::clear()
{
    types = j_ling_type::None;
    msgs_to_proc = 0;
    msgs_ready = 0;
    is_configured = false;
    ling_list.clear();
    ling_stats->clear();
}

j_ling_type j_linguist::char_category(const QChar t)
{
    switch (t.category())
    {
    case QChar::Letter_Lowercase:
    case QChar::Letter_Uppercase:
        return j_ling_type::Word;
    case QChar::Number_DecimalDigit:
        return j_ling_type::Number;
    case QChar::Symbol_Math:
    case QChar::Symbol_Currency:
    case QChar::Symbol_Other:
        return j_ling_type::Symbol;
    case QChar::Punctuation_Connector:
    case QChar::Punctuation_Open:
    case QChar::Punctuation_Close:
    case QChar::Punctuation_Other:
        return j_ling_type::Sign;
    case QChar::Separator_Space:
    case QChar::Separator_Line:
    case QChar::Separator_Paragraph:
        return j_ling_type::Separator;
    default:
        return j_ling_type::ND;
    }
    return j_ling_type::ND;
}

j_lang j_linguist::char_language(const QChar t)
{
    if ((t >= QChar(65) && t <= QChar(90)) ||
        (t >= QChar(97) && t <= QChar(122)))
        /// latin upper and lower case
        return j_lang::Eng;
    else if (t >= QChar(1040) && t <= QChar(1105))
        /// cyrillic upper and lower case
        return j_lang::Rus;
    else
        /// another char
        return j_lang::ND;
}

j_lang j_linguist::ling_language(bool ling_start, j_lang previous, const QChar current)
{
    j_lang curr_lang = char_language(current);
    if (ling_start || previous == curr_lang)
        return curr_lang;
    else
        return j_lang::ND;
}
