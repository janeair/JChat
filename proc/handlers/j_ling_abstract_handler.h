#ifndef J_LING_ABSTRACT_HANDLER_H
#define J_LING_ABSTRACT_HANDLER_H

#include <QObject>
#include <QDebug>

#include "common/j_ling.h"
#include "common/j_msgs_property_stats.h"

enum class j_handler_id
{
    NoHandler = 0x0,
    GWHandler = 0x1,
    AllHandlers = 0x1,
};

QString enum_to_string(j_handler_id t);

Q_DECLARE_FLAGS(j_handlers, j_handler_id);

class j_ling_abstract_handler : public QObject
{
    Q_OBJECT

public:
    explicit j_ling_abstract_handler(j_handler_id type, j_langs proc_langs, j_ling_types proc_types, QObject *parent = nullptr);
    ~j_ling_abstract_handler() = default;

    virtual void process_msg(QList<j_ling> msg) = 0;
    bool is_busy() const { return busy; }
    j_handler_id id() const { return handler_type; }
    j_langs langs() const { return languages; }
    j_ling_types types() const { return ling_types; }

signals:
    void stats_ready(j_msgs_property_stats stats);

protected:
    void work() { busy = !busy; }

private:
    bool busy = false;
    const j_handler_id handler_type;
    const j_langs languages;
    const j_ling_types ling_types;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(j_handlers);

#endif // J_LING_ABSTRACT_HANDLER_H
