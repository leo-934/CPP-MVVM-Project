#pragma once

#include <QMainWindow>
//#include <QGridLayout>
//#include <QPushButton>
#include "def.h"
#include "ui_mainview.h"
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
	ptr<QLabel> latexLabel;
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
	ptr<QImage> svgPtr;

	const QString defaultText = "No image loaded";

	eventId getLatexFromBase64;
	eventId getSvgFromLatexString;
	eventId prettifyLatexString;
	
	
	//data need to be stored for a while
	QString filePath;
	QString latexString;

	Ui::ViewClass ui;

	void initSlots();
	void initMenu();
	void initDefaultContent();

	void changeLatexToLabel() {
		latexLabel->setHidden(false);
		latexEditor->setHidden(true);
	}
	void changeLatexToEditor() {
		latexLabel->setHidden(true);
		latexEditor->setHidden(false);
	}

	void setImg(ptr<QImage> tmpImg);

public:
	void init();
	
	
	//所有数据的更改必须使用set函数，不可直接访问私有数据成员，因为set函数内部还会操控组件更改。


	//svg don't need a getter because it comes from viewmodel
	void setSvg(const ptr<QImage> tmpSvgPtr);

	//imgptr's setter need to be private. 
	const ptr<QImage> getImg();

	void setFilePath(const QString& filePath);
	const QString& getFilePath();
	
	void setLatexString(const QString& tmpString);
	const QString& getLatexString();

	BIND_TEMPLATE(getLatexFromBase64)
	BIND_TEMPLATE(getSvgFromLatexString)
	BIND_TEMPLATE(prettifyLatexString)

};
