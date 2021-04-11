//#include "app.h"
#include "viewmodel.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewModel viewModel;
    viewModel.run();
    return a.exec();
}
