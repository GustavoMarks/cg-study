#include <GL/glut.h>

class Window
{
public:
	Window(int argc, char **argv, int width = 800, int height = 600, const char *title = "");
	void static update();
};