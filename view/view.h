#pragma once

#include <QMainWindow>
//#include <QGridLayout>
//#include <QPushButton>
#include "def.h"
#include "ui_view.h"


class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = Q_NULLPTR);

private:
    static void onLoadButtonClicked();
    static void onResetButtonClicked();
    static void onEditButtonClicked();
    static void onApplyButtonClicked();
    static void onDownloadButtonClicked();
    static void onPrettifyButtonClicked();
    static void onCalculateButtonClicked();

    ptr<QGridLayout> gridLayoutParent;

    ptr<QLabel> imgLabel;
    ptr<QTextEdit> latexEditor;
    ptr<QGridLayout> gridLayoutSon;

    ptr<QPushButton> loadButton;
    ptr<QPushButton> resetButton;

    ptr<QPushButton> editButton;
    ptr<QPushButton> applyButton;
    ptr<QPushButton> downloadButton;
    ptr<QPushButton> prettifyButton;

    ptr<QTextEdit> filePathEditor;

    ptr<QPushButton> calculateButton;
    
    ptr<QLabel> systemOperationsLabel;
    ptr<QLabel> latexOperationsLabel;

    ptr<QMenuBar> menuBar;
    //ptr<QMenu> fileMenu;
    //ptr<QMenu> aboutMenu;

    Ui::ViewClass ui;

public:
    void init();
    void initSlots();
    void initMenu();
};
