#include "jchat.h"

#include <QApplication>
#include <QStyleFactory>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    jchat w;
    return a.exec();
}
