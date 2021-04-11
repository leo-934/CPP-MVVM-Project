#pragma once

#include <QMainWindow>
//#include <QGridLayout>
//#include <QPushButton>
#include "def.h"
#include "ui_view.h"
#include "event.h"

class MainView : public QMainWindow
{
	Q_OBJECT

public:
	MainView(QWidget* parent = Q_NULLPTR);

private slots:
	void onLoadButtonClicked();
	void onResetButtonClicked();
	void onEditButtonClicked();
	void onApplyButtonClicked();
	void onDownloadButtonClicked();
	void onPrettifyButtonClicked();
	void onCalculateButtonClicked();

private:
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

	eventId loadImage;
	
	//data
	QString filePath;

	Ui::ViewClass ui;

public:
	void init();
	void initSlots();
	void initMenu();
	void initDefaultText();
	
	//所有数据的更改必须使用set函数，不可直接访问私有数据成员，因为set函数内部还会操控组件更改。

	void setFilePath(const QString& filePath);
	const QString& getFilePath();
	
	void bindloadImage(workFunctionNoAll function);

};
