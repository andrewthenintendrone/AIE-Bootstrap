#include "Application3D.h"

int main() {
	
	auto app = new Application3D();
	app->run("AIE", 400, 240, false);
	delete app;

	return 0;
}