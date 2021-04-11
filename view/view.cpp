#include "view.h"
#include "stylesheet.h"

#include <memory>

#include <QDebug>
#include <QFileDialog>

MainView::MainView(QWidget* parent)
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

void MainView::onLoadButtonClicked()
{
	qDebug() << "loadbutton clicked";

	auto path = QFileDialog::getOpenFileName(
		NULL,
		"select an image file",
		"C:\\",
		"Images(*.png * .jpg)"
	);
	qDebug() << path;

	setFilePath(filePath);
	EventManager::raiseEvent(loadImage);
}

void MainView::onResetButtonClicked()
{
	qDebug() << "resetbutton clicked";
	initDefaultText();
}

void MainView::onEditButtonClicked()
{
	qDebug() << "editbutton clicked";
}

void MainView::onApplyButtonClicked()
{
	qDebug() << "applybutton clicked";
}

void MainView::onDownloadButtonClicked()
{
	qDebug() << "downloadbutton clicked";
}

void MainView::onPrettifyButtonClicked()
{
	qDebug() << "prettifybutton clicked";
}

void MainView::onCalculateButtonClicked()
{
	qDebug() << "calculateButton clicked";
}

void MainView::init()
{
	setWindowTitle("Welcome!");
	setMinimumSize(960, 600);
	setStyleSheet(backgroundPink);

	latexEditor->setStyleSheet(backgroundWhite);

	imgLabel->setStyleSheet(backgroundWhite);
	latexEditor->setStyleSheet(backgroundWhite);

	loadButton->setStyleSheet(backgroundWhite);
	resetButton->setStyleSheet(backgroundWhite);

	editButton->setStyleSheet(backgroundWhite);
	applyButton->setStyleSheet(backgroundWhite);
	downloadButton->setStyleSheet(backgroundWhite);
	prettifyButton->setStyleSheet(backgroundWhite);

	filePathEditor->setStyleSheet(backgroundWhite);

	calculateButton->setStyleSheet(backgroundWhite);

	systemOperationsLabel->setStyleSheet(backgroundWhite);
	latexOperationsLabel->setStyleSheet(backgroundWhite);

	initSlots();
	initMenu();
	initDefaultText();
}

void MainView::initSlots()
{
	connect(loadButton.get(), &QPushButton::clicked, this, &MainView::onLoadButtonClicked);
	connect(resetButton.get(), &QPushButton::clicked, this, &MainView::onResetButtonClicked);
	connect(applyButton.get(), &QPushButton::clicked, this, &MainView::onApplyButtonClicked);
	connect(editButton.get(), &QPushButton::clicked, this, &MainView::onEditButtonClicked);
	connect(downloadButton.get(), &QPushButton::clicked, this, &MainView::onDownloadButtonClicked);
	connect(prettifyButton.get(), &QPushButton::clicked, this, &MainView::onPrettifyButtonClicked);
	connect(calculateButton.get(), &QPushButton::clicked, this, &MainView::onCalculateButtonClicked);

}

void MainView::initMenu()
{
	auto fileMenu = menuBar->addMenu("File");
	auto loadAction = fileMenu->addAction("Load");
	connect(loadAction, &QAction::triggered, this, &MainView::onLoadButtonClicked);
	auto downloadAction = fileMenu->addAction("Download");
	connect(downloadAction, &QAction::triggered, this, &MainView::onDownloadButtonClicked);
	auto exitAction = fileMenu->addAction("Exit");
	connect(exitAction, &QAction::triggered, this, [&]() {
		qDebug() << "exit";
		exit(0);
		});
	//about菜单还没有connect槽函数
	auto aboutAction = menuBar->addAction("About");


}

void MainView::initDefaultText()
{
	const QString defaultText = "No image loaded";
	imgLabel->setText(defaultText);
	latexEditor->setText(defaultText);
	filePathEditor->setText(defaultText);
}

void MainView::setFilePath(const QString& path)
{
	filePath = path;
	filePathEditor->setText(filePath);
}

const QString& MainView::getFilePath()
{
	return filePath;
	// TODO: insert return statement here
}

void MainView::bindloadImage(workFunctionNoAll function)
{
	loadImage = EventManager::registerEvent(function);
	
}




