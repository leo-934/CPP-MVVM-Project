#pragma once
#include "def.h"
#include "mainview.h"
#include "remotemodel.h"
#include <QString>
#include <QSvgRenderer>
#include <QByteArray>
#include <QPainter>
#include "document.h"
class ViewModel {
private:
	
	ptr<RemoteModel> remoteModel;
	ptr<MainView> mainView;

	//view to vm to model
	callbackFunction getLatexFromBase64;
	callbackFunction getSvgFromLatexString;
	callbackFunction prettifyLatexString;

	//model to vm to view
	callbackFunction getLatexJsonSuccess;
	callbackFunction getLatexJsonFail;
	callbackFunction getSvgFromLatexStringSuccess;
	callbackFunction getSvgFromLatexStringFail;

	//两次更改之间可重用多次的数据会留在vm中，每次更改后只使用一次的不会。

	void initBind();
	


	void bindMainViewToViewModel();
	void bindViewModelToRemoteModel(ptr<RemoteModel> model);
	void bindRemoteModelToViewModel();
	void bindViewModelToMainView(ptr<MainView> view);

	std::string convertLatexJsonToLatexString(std::string latexJson);
public:

	void run();
};