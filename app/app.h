#pragma once
#include "view.h"
#include "viewmodel.h"
#include "model.h"

class App {
private:
	ptr<MainView> view;
	ptr<ViewModel> viewmodel;
	ptr<LocalModel> model;
public:
	App();
	void run();
	//void bindViewAndViewModel();

	
};