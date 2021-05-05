//#include "app.h"
#include "viewmodel.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QString>
#include "HttpManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewModel viewModel;
    viewModel.run();
    //qDebug() << QString(HttpManager::qwe().c_str());
    return a.exec();
}
