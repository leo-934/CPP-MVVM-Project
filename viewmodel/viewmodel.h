#pragma once
#include "def.h"
#include "mainview.h"
#include "remotemodel.h"
#include <QString>

class ViewModel {
private:
	
	ptr<RemoteModel> remoteModel;
	ptr<MainView> mainView;

	callbackFunction getLatexFromBase64;
	
	//两次更改之间可重用多次的数据会留在vm中，每次更改后只使用一次的不会。

public:

	void run();

	void bindMainView(ptr<MainView> view);
	void bindLocalModel(ptr<RemoteModel> model);
};