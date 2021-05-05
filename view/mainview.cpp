#include "mainview.h"
#include "stylesheet.h"

#include <memory>
#include <exception>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>

MainView::MainView(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	gridLayoutParent = ptr<QGridLayout>(ui.gridLayoutParent);

	imgLabel = ptr<QLabel>(ui.imgLabel);
	latexLabel = std::make_shared<QLabel>();
	latexEditor = ptr<QTextEdit>(ui.latexEditor);
	gridLayoutSon = ptr<QGridLayout>(ui.gridLayoutSon);

	loadButton = ptr<QPushButton>(ui.loadButton);
	ocrButton = ptr<QPushButton>(ui.ocrButton);
	resetButton = ptr<QPushButton>(ui.resetButton);

	editButton = ptr<QPushButton>(ui.editButton);
	applyButton = ptr<QPushButton>(ui.applyButton);
	downloadButton = ptr<QPushButton>(ui.DownloadButton);
	prettifyButton = ptr<QPushButton>(ui.prettifyButton);

	filePathBrowser = ptr<QTextBrowser>(ui.filePathBrowser);

	calculateButton = ptr<QPushButton>(ui.calculateButton);

	systemOperationsLabel = ptr<QLabel>(ui.systemOperationsLabel);
	latexOperationsLabel = ptr<QLabel>(ui.latexOperationsLabel);

	menuBar = ptr<QMenuBar>(ui.menuBar);

	gridLayoutParent->addWidget(latexLabel.get(), 1, 0);

}

void MainView::onLoadButtonClicked()
{
	qDebug() << "loadbutton clicked";

	auto path = QFileDialog::getOpenFileName(
		NULL,
		"select an image file",
		"C:\\",
		"image(*.png * .jpg)"
	);
	qDebug() << path;

	setFilePath(path);

	if (filePath != "") {
		try {
			setImg(std::make_shared<QImage>(filePath));
		}
		catch (std::exception& e) {
			qDebug() << e.what();
		}
	}
	else {
		qDebug()<< "invalid filePath";
	}
	
	
}

void MainView::onOcrButtonClicked()
{
	if (filePath == defaultText) {
		QMessageBox::about(NULL, "error", "No image loaded\nPlease load an image before ocr");
	}
	else if (filePath != "") {
		//raise a event to ocr

		EventManager::raiseEvent(getLatexFromBase64);
		changeLatexToEditor();
	}
	else {
		throw std::exception("invalid filePath");
	}
}

void MainView::onResetButtonClicked()
{
	qDebug() << "resetbutton clicked";
	initDefaultContent();
}

void MainView::onEditButtonClicked()
{
	qDebug() << "editbutton clicked";
	changeLatexToEditor();
}

void MainView::onApplyButtonClicked()
{
	changeLatexToLabel();
	setLatexString(latexEditor->toPlainText());
	EventManager::raiseEvent(getSvgFromLatexString);
	qDebug() << "applybutton clicked";
}

void MainView::onDownloadButtonClicked()
{
	QString savePath = QFileDialog::getSaveFileName(
		this,
		"save image",
		"",
		"all"
	);
	if (!savePath.isEmpty()) {
		if (!(imgPtr->save(savePath))) {
			QMessageBox::information(
				this,
				"error",
				"can't save image"
			);
		}
	}
	else {
		QMessageBox::information(
			this,
			"error",
			"savePath can't be empty"
		);
	}
	qDebug() << "downloadbutton clicked";
}

void MainView::onPrettifyButtonClicked()
{
	EventManager::raiseEvent(prettifyLatexString);
	qDebug() << "prettifybutton clicked";
}

void MainView::onCalculateButtonClicked()
{
	qDebug() << "calculateButton clicked";
}

void MainView::setImg(ptr<QImage> tmpImg)
{

	imgPtr = tmpImg;
	imgLabel->setPixmap(QPixmap::fromImage(*imgPtr));
}

void MainView::init()
{
	setWindowTitle("Welcome!");
	setMinimumSize(960, 600);
	setStyleSheet(backgroundPink);

	latexEditor->setStyleSheet(backgroundWhite);

	imgLabel->setStyleSheet(backgroundWhite);
	latexLabel->setStyleSheet(backgroundWhite);
	latexEditor->setStyleSheet(backgroundWhite);

	loadButton->setStyleSheet(backgroundWhite);
	ocrButton->setStyleSheet(backgroundWhite);
	resetButton->setStyleSheet(backgroundWhite);

	editButton->setStyleSheet(backgroundWhite);
	applyButton->setStyleSheet(backgroundWhite);
	downloadButton->setStyleSheet(backgroundWhite);
	prettifyButton->setStyleSheet(backgroundWhite);

	filePathBrowser->setStyleSheet(backgroundWhite);

	calculateButton->setStyleSheet(backgroundWhite);

	systemOperationsLabel->setStyleSheet(backgroundWhite);
	latexOperationsLabel->setStyleSheet(backgroundWhite);

	changeLatexToLabel();
	latexLabel->setAlignment(Qt::AlignCenter);

	initSlots();
	initMenu();
	initDefaultContent();
}

void MainView::initSlots()
{
	connect(loadButton.get(), &QPushButton::clicked, this, &MainView::onLoadButtonClicked);
	connect(ocrButton.get(), &QPushButton::clicked, this, &MainView::onOcrButtonClicked);
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

void MainView::initDefaultContent()
{
	imgLabel->setText(defaultText);
	setLatexString(defaultText);
	setFilePath(defaultText);
}

void MainView::setSvg(const ptr<QImage> tmpSvgPtr)
{
	svgPtr = tmpSvgPtr;
	latexLabel->setPixmap(QPixmap::fromImage(*svgPtr));
	
}

const ptr<QImage> MainView::getImg()
{
	return imgPtr;
}

void MainView::setFilePath(const QString& path)
{
	filePath = path;
	filePathBrowser->setText(filePath);
}

const QString& MainView::getFilePath()
{
	return filePath;
	// TODO: insert return statement here
}

void MainView::setLatexString(const QString& tmpString)
{
	latexString = tmpString;
	latexEditor->setText(tmpString);
}

const QString& MainView::getLatexString()
{
	return latexString;
	// TODO: insert return statement here
}





