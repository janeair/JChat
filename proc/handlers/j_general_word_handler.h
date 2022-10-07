#ifndef J_GENERAL_WORD_HANDLER_H
#define J_GENERAL_WORD_HANDLER_H

#include "proc/handlers/j_ling_abstract_handler.h"

class j_general_word_handler : public j_ling_abstract_handler
{
    Q_OBJECT

public:
    j_general_word_handler(QObject* parent);
    ~j_general_word_handler() = default;

    virtual void process_msg(QList<j_ling> msg) override;
};

#endif // J_GENERAL_WORD_HANDLER_H
