#include "app.h"
#include "view.h"
void App::run()
{
	view = std::make_shared<View>();

	view->init();
	view->show();
}
