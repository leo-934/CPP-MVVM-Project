#include "viewmodel.h"

void ViewModel::run()
{
	//bind 注意绑定顺序，必须按照数据流向反向绑定，否则function还没有内容就被绑定了
	bindLocalModel(std::make_shared<LocalModel>());
	bindMainView(std::make_shared<MainView>());
	

	//init and run
	mainView->init();
	mainView->show();

}

void ViewModel::bindMainView(ptr<MainView> view)
{
	mainView = view;

	//bind view to viewmodel
	mainView->bindloadImage(getLatexFromImage);

}

void ViewModel::bindLocalModel(ptr<LocalModel> model)
{
	localModel = model;
	
	//bind viewmodel to localmodel
	getLatexFromImage = [this]() {
		auto path = mainView->getFilePath();
		localModel->getLatexFromImage(path.toStdString());
	};
}
