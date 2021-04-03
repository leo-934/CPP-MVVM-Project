#pragma once

#include <QMainWindow>
#include "ui_view.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = Q_NULLPTR);

private:
    Ui::ViewClass ui;
};
