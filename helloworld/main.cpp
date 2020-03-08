#include "hellodialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hellodialog w;
    w.show();
    return a.exec();
}
