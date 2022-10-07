#include "j_processor.h"

#include "common/j_msgs_property_stats.h"
#include "proc/handlers/j_general_word_handler.h"

#include <QDebug>

j_processor::j_processor(QObject *parent) : QObject(parent)
{
    text_stats = new j_msgs_property_stats();
}

bool j_processor::is_busy() const
{
    if (buffer.size() > 0 || msgs_ready < msgs_to_proc)
        return true;
    for (j_ling_abstract_handler* hndl : handlers)
        if (hndl->is_busy())
            return true;
    return false;
}

const j_msgs_property_stats j_processor::stats() const
{
    return *text_stats;
}

void j_processor::configure_settings(uint32_t msgs_count, j_handlers handler_types)
{
    qDebug() << "processor: configure settings" << msgs_count << handler_types;
    assert(msgs_count > 0);
    msgs_to_proc = msgs_count;
    assert(handlers.size() == 0);
    if (handler_types.testFlag(j_handler_id::GWHandler))
    {
        j_general_word_handler* hndl = new j_general_word_handler(this);
        handlers.push_back(hndl);
    }

    for (std::vector<j_ling_abstract_handler*>::const_iterator i = handlers.cbegin(); i != handlers.cend(); ++i)
        connect((*i), &j_ling_abstract_handler::stats_ready, this, &j_processor::add_stats);

    is_configured = true;
}

void j_processor::put_to_buffer(QList<j_ling> lings)
{
    buffer.push_back(lings);
    if (buffer.size() > 0)
        process_msgs();
}

void j_processor::process_msgs()
{
    if (!is_configured)
        return;
    while (buffer.size() > 0)
    {
        QList<j_ling> msg;
        {
            msg = buffer.front();
            buffer.pop_front();
        }
        for (j_ling_abstract_handler* hndl : handlers)
            hndl->process_msg(msg);
        msgs_ready++;
    }
    if (!is_busy())
    {
        emit stats_to_gui(*text_stats);
        emit to_compare(std::move(*text_stats));
        clear();
    }
}

void j_processor::add_stats(j_msgs_property_stats stats)
{
    text_stats->join(&stats, j_stats_join_t::Merge);
}

void j_processor::clear()
{
    msgs_to_proc = 0;
    msgs_ready = 0;
    is_configured = false;
    text_stats->clear();
    handlers.clear();
    buffer.clear();
}
