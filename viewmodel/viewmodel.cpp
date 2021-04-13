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

}

void ViewModel::bindViewModelToRemoteModel(ptr<RemoteModel> model)
{
	remoteModel = model;

	//bind viewmodel to remotemodel
	getLatexFromBase64 = [this]() {
		auto imgPtr = mainView->getImgPtr();
		QByteArray byteArray;
		QBuffer buffer(&byteArray);
		imgPtr->save(&buffer, "PNG");
		auto imgBase64 = QString::fromLatin1(byteArray.toBase64().data());
		remoteModel->getLatexJsonFromBase64(imgBase64.toStdString());
	};

}

void ViewModel::bindRemoteModelToViewModel()
{
	
	//bind remotemodel to localmodel;
	remoteModel->bindgetLatexJsonSuccess(getLatexJsonSuccess);
	remoteModel->bindgetLatexJsonFail(getLatexJsonFail);
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
}

std::string ViewModel::convertLatexJsonToLatexString(std::string latexJson)
{
	//parse json
	qDebug() << QString::fromStdString(latexJson);
	rapidjson::Document document;
	document.Parse(latexJson.c_str());
	return document["words_result"][0]["words"].GetString();
}
