#include "viewmodel.h"

void ViewModel::run()
{
	//bind 注意绑定顺序，必须按照数据流向反向绑定，否则function还没有内容就被绑定了
	bindLocalModel(std::make_shared<RemoteModel>());
	bindMainView(std::make_shared<MainView>());
	

	//init and run
	mainView->init();
	mainView->show();

}

void ViewModel::bindMainView(ptr<MainView> view)
{
	mainView = view;

	//bind view to viewmodel
	mainView->bindGetLatexFromBase64(getLatexFromBase64);

}

void ViewModel::bindLocalModel(ptr<RemoteModel> model)
{
	remoteModel = model;
	
	//bind viewmodel to localmodel
	getLatexFromBase64 = [this]() {
		auto imgPtr = mainView->getImgPtr();
		// 四月十二日晚十一点停在这里去洗澡
		remoteModel->getLatexFromBase64(path.toStdString());
	};
}
