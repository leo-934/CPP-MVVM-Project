#pragma once
#include "def.h"
#include "mainview.h"
#include "remotemodel.h"
#include <QString>
#include "document.h"
class ViewModel {
private:
	
	ptr<RemoteModel> remoteModel;
	ptr<MainView> mainView;

	//view to vm
	callbackFunction getLatexFromBase64;

	//model to vm
	callbackFunction getLatexJsonSuccess;
	callbackFunction getLatexJsonFail;

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