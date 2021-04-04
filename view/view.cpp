#include "view.h"
#include "stylesheet.h"
#include <memory>
#include <QDebug>
View::View(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	gridLayoutParent = ptr<QGridLayout>(ui.gridLayoutParent);

	imgLabel = ptr<QLabel>(ui.imgLabel);
	latexEditor = ptr<QTextEdit>(ui.latexEditor);
	gridLayoutSon = ptr<QGridLayout>(ui.gridLayoutSon);

	loadButton = ptr<QPushButton>(ui.loadButton);
	resetButton = ptr<QPushButton>(ui.resetButton);

	editButton = ptr<QPushButton>(ui.editButton);
	applyButton = ptr<QPushButton>(ui.applyButton);
	downloadButton = ptr<QPushButton>(ui.DownloadButton);
	prettifyButton = ptr<QPushButton>(ui.prettifyButton);

	filePathEditor = ptr<QTextEdit>(ui.filePathEditor);

	calculateButton = ptr<QPushButton>(ui.calculateButton);

	systemOperationsLabel = ptr<QLabel>(ui.systemOperationsLabel);
	latexOperationsLabel = ptr<QLabel>(ui.latexOperationsLabel);

	menuBar = ptr<QMenuBar>(ui.menuBar);
}

void View::onLoadButtonClicked()
{
	qDebug() << "loadbutton clicked";
}

void View::onResetButtonClicked()
{
	qDebug() << "resetbutton clicked";
}

void View::onEditButtonClicked()
{
	qDebug() << "editbutton clicked";
}

void View::onApplyButtonClicked()
{
	qDebug() << "applybutton clicked";
}

void View::onDownloadButtonClicked()
{
	qDebug() << "downloadbutton clicked";
}

void View::onPrettifyButtonClicked()
{
	qDebug() << "prettifybutton clicked";
}

void View::onCalculateButtonClicked()
{
	qDebug() << "calculateButton clicked";
}

void View::init()
{
	setWindowTitle("Welcome!");
	setMinimumSize(960, 600);
	setStyleSheet(backgroundpink);

	latexEditor->setStyleSheet(backgroundwhite);

	imgLabel->setStyleSheet(backgroundwhite);
	latexEditor->setStyleSheet(backgroundwhite);

	loadButton->setStyleSheet(backgroundwhite);
	resetButton->setStyleSheet(backgroundwhite);

	editButton->setStyleSheet(backgroundwhite);
	applyButton->setStyleSheet(backgroundwhite);
	downloadButton->setStyleSheet(backgroundwhite);
	prettifyButton->setStyleSheet(backgroundwhite);

	filePathEditor->setStyleSheet(backgroundwhite);

	calculateButton->setStyleSheet(backgroundwhite);

	systemOperationsLabel->setStyleSheet(backgroundwhite);
	latexOperationsLabel->setStyleSheet(backgroundwhite);

	initSlots();
	initMenu();
}

void View::initSlots()
{
	connect(loadButton.get(), &QPushButton::clicked, this, &onLoadButtonClicked);
	connect(resetButton.get(), &QPushButton::clicked, this, &onResetButtonClicked);
	connect(applyButton.get(), &QPushButton::clicked, this, &onApplyButtonClicked);
	connect(editButton.get(), &QPushButton::clicked, this, &onEditButtonClicked);
	connect(downloadButton.get(), &QPushButton::clicked, this, &onDownloadButtonClicked);
	connect(prettifyButton.get(), &QPushButton::clicked, this, &onPrettifyButtonClicked);
	connect(calculateButton.get(), &QPushButton::clicked, this, &onCalculateButtonClicked);

}

void View::initMenu()
{
	auto fileMenu = menuBar->addMenu("File");
	auto loadAction = fileMenu->addAction("Load");
	connect(loadAction, &QAction::triggered, this, &onLoadButtonClicked);
	auto downloadAction = fileMenu->addAction("Download");
	connect(downloadAction, &QAction::triggered, this, &onDownloadButtonClicked);
	auto exitAction = fileMenu->addAction("Exit");
	connect(exitAction, &QAction::triggered, this, [&]() {
		qDebug() << "exit";
		exit(0);
		});
	//about菜单还没有connect槽函数
	auto aboutAction = menuBar->addAction("About");
	

}
