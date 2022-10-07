#ifndef J_PROCESSOR_H
#define J_PROCESSOR_H

#include <QObject>

#include "common/j_ling.h"
#include "proc/handlers/j_ling_abstract_handler.h"

class j_msgs_property_stats;

class j_processor : public QObject
{
    Q_OBJECT

public:
    explicit j_processor(QObject *parent = nullptr);
    ~j_processor() = default;

    bool is_busy() const;
    const j_msgs_property_stats stats() const;

signals:
    void stats_to_gui(j_msgs_property_stats stats);
    void to_compare(j_msgs_property_stats stats);

public slots:
    void configure_settings(uint32_t msgs_count, j_handlers handler_types);
    void put_to_buffer(QList<j_ling> lings);

private slots:
    void add_stats(j_msgs_property_stats stats);

private:
    uint32_t msgs_to_proc = 0;
    uint32_t msgs_ready = 0;
    bool is_configured = false;
    QVector<QList<j_ling>> buffer = { };
    std::vector<j_ling_abstract_handler*> handlers = { };
    j_msgs_property_stats* text_stats = nullptr;

    void clear();
    void process_msgs();

};

#endif // J_PROCESSOR_H
