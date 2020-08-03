#include "choosedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    chooseDialog w;
    w.show();
    return a.exec();
}
