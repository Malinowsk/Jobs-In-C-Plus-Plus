#include "colectivos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Colectivos w;
    w.show();
    return a.exec();
}
