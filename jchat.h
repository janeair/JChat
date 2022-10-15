#ifndef JCHAT_H
#define JCHAT_H

#include <QObject>

#include "gui/jchat_gui.h"
#include "proc/j_linguist.h"
#include "proc/j_processor.h"
#include "proc/j_comparator.h"
#include "load/j_profile_loader.h"

class jchat : public QObject
{
    Q_OBJECT

public:
    jchat();
    ~jchat() = default;

private:
    std::unique_ptr<jchat_gui>          gui         = nullptr;
    std::unique_ptr<j_linguist>         linguist    = nullptr;
    std::unique_ptr<j_processor>        processor   = nullptr;
    std::unique_ptr<j_comparator>       comparator  = nullptr;
    std::unique_ptr<j_profile_loader>   loader      = nullptr;
};

#endif // JCHAT_H
