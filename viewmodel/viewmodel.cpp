#include "viewmodel.h"
#include "QBuffer"
#include "qDebug"
void ViewModel::run()
{
	
	initBind();
	//init and show view;
	mainView->init();
	mainView->show();

}

void ViewModel::initBind()
{
	//bind 注意绑定顺序，必须按照数据流向反向绑定，否则function还没有内容就被绑定了

	
	bindViewModelToRemoteModel(std::make_shared<RemoteModel>());
	bindViewModelToMainView(std::make_shared<MainView>());
	bindMainViewToViewModel();
	bindRemoteModelToViewModel();
	

}

void ViewModel::bindMainViewToViewModel()
{
	
	//bind view to viewmodel
	mainView->bindgetLatexFromBase64(getLatexFromBase64);
	mainView->bindgetSvgFromLatexString(getSvgFromLatexString);
	mainView->bindprettifyLatexString(prettifyLatexString);
	
}

void ViewModel::bindViewModelToRemoteModel(ptr<RemoteModel> model)
{
	remoteModel = model;

	//bind viewmodel to remotemodel
	getLatexFromBase64 = [this]() {
		auto imgPtr = mainView->getImg();
		QByteArray byteArray;
		QBuffer buffer(&byteArray);
		imgPtr->save(&buffer, "PNG");
		auto imgBase64 = QString::fromLatin1(byteArray.toBase64().data());
		remoteModel->getLatexJsonFromBase64(imgBase64.toStdString());
	};
	getSvgFromLatexString = [this]() {
		auto latexString = mainView->getLatexString();
		remoteModel->getSvgFromLatexString(latexString.toStdString());
	};
	
}

void ViewModel::bindRemoteModelToViewModel()
{
	
	//bind remotemodel to localmodel;
	remoteModel->bindgetLatexJsonSuccess(getLatexJsonSuccess);
	remoteModel->bindgetLatexJsonFail(getLatexJsonFail);

	remoteModel->bindgetSvgFromLatexStringSuccess(getSvgFromLatexStringSuccess);
	remoteModel->bindgetSvgFromLatexStringFail(getSvgFromLatexStringFail);
}

void ViewModel::bindViewModelToMainView(ptr<MainView> view)
{
	mainView = view;

	//bind viewmodel to view
	getLatexJsonSuccess = [this]() {
		auto latexJson = remoteModel->getLatexJson();

		//json parse need to be written here
		latexJson = convertLatexJsonToLatexString(latexJson);

		mainView->setLatexString(QString::fromStdString(latexJson));
	};

	getLatexJsonFail = [this]() {

	};

	getSvgFromLatexStringSuccess = [this]() {
		auto svgByteArray = QString::fromStdString(remoteModel->getSvg()).toLatin1();
		QSvgRenderer renderer(svgByteArray);
		auto svgImage = std::make_shared<QImage>(500, 200, QImage::Format_ARGB32);
		QPainter painter(svgImage.get());
		renderer.render(&painter);
		mainView->setSvg(svgImage);
	};

	getSvgFromLatexStringFail = [this]() {

	};
	prettifyLatexString = [this]() {
		auto latexString = mainView->getLatexString().toStdString();
		std::string tmp;
		for (auto i : latexString) {
			if (i != ' ') tmp.push_back(i);
		}
		mainView->setLatexString(QString::fromStdString(tmp));
	};
}

std::string ViewModel::convertLatexJsonToLatexString(std::string latexJson)
{
	//parse json
	qDebug() << QString::fromStdString(latexJson);
	rapidjson::Document document;
	document.Parse(latexJson.c_str());
	return document["words_result"][0]["words"].GetString();
}

