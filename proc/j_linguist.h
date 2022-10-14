#ifndef J_LINGUIST_H
#define J_LINGUIST_H

#include <QObject>

#include "common/ling/j_ling.h"
#include "common/stats/j_msgs_general_stats.h"

class j_linguist : public QObject
{
    Q_OBJECT

public:
    explicit j_linguist(QObject *parent = nullptr);

public slots:
    void configure_settings(uint32_t msgs, j_ling_types t);
    void process_msg(QString msg);

signals:
    void to_process(QList<j_ling> msg);
    void lings_to_gui(QList<j_ling> lings);
    void stats_to_gui(j_msgs_general_stats stats);

public:
    bool is_busy() const;
    void clear();
    j_ling_type static char_category(const QChar t);
    j_lang static char_language(const QChar t);
    j_lang static ling_language(bool ling_start, j_lang previous, const QChar current);

private:
    j_ling_types types = j_ling_type::None;
    uint32_t msgs_to_proc = 0;
    uint32_t msgs_ready = 0;
    bool is_configured = false;
    QList<j_ling> ling_list;
    j_msgs_general_stats* ling_stats = nullptr;
};

#endif // J_LINGUIST_H
