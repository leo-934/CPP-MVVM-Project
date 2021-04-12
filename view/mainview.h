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
	void onOcrButtonClicked();
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
	ptr<QPushButton> ocrButton;
	ptr<QPushButton> resetButton;

	ptr<QPushButton> editButton;
	ptr<QPushButton> applyButton;
	ptr<QPushButton> downloadButton;
	ptr<QPushButton> prettifyButton;

	ptr<QTextBrowser> filePathBrowser;

	ptr<QPushButton> calculateButton;

	ptr<QLabel> systemOperationsLabel;
	ptr<QLabel> latexOperationsLabel;

	ptr<QMenuBar> menuBar;

	ptr<QImage> imgPtr;

	const QString defaultText = "No image loaded";

	eventId getLatexFromBase64;

	
	
	//data need to be stored for a while
	QString filePath;
	QString latexString;

	Ui::ViewClass ui;

public:
	void init();
	void initSlots();
	void initMenu();
	void initDefaultContent();
	
	//所有数据的更改必须使用set函数，不可直接访问私有数据成员，因为set函数内部还会操控组件更改。

	//imgptr don't need a setter.
	const ptr<QImage> getImgPtr();

	void setFilePath(const QString& filePath);
	const QString& getFilePath();
	
	void setLatexString(const QString& tmpString);
	const QString& getLatexString();

	void bindGetLatexFromBase64(workFunctionNoAll function);

};
