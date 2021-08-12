#include "sortingclass.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SortingClass w;
    w.show();
    return a.exec();
}
