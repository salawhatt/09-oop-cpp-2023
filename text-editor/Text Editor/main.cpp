#include "TUIAdapter.h"
#include "Controller.h"

int main(int argc, char* argv[])
{
	View* view = new View();
	Model* model = new Model(view->getWindowSize().second);
	Controller* controller = new Controller(model, view);
	controller->loop();
	delete controller;
	delete view;
	delete model;
	return 0;
}