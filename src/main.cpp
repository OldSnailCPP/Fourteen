#pragma comment(lib, "user32.lib")

#include <QApplication>
#include "frameless.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FramelessWindow w;
    w.show();
    return a.exec();
}
