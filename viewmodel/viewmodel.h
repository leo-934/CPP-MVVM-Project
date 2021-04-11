#pragma once
#include "def.h"
#include "view.h"
#include "model.h"
#include <QString>

class ViewModel {
private:
	
	ptr<LocalModel> localModel;
	ptr<MainView> mainView;

	callbackFunction getLatexFromImage;
	
	//两次更改之间可重用多次的数据会留在vm中，每次更改后只使用一次的不会。

public:

	void run();

	void bindMainView(ptr<MainView> view);
	void bindLocalModel(ptr<LocalModel> model);
};