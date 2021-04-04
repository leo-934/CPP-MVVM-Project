#include "app.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App app;
    app.run();
    return a.exec();
}
