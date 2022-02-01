#include <GL/glut.h>
#include "../../components/RayCasting/RayCasting.hpp"

class Window
{
public:
	Window(int argc, char **argv, int width, int height, const char *title, RGB **setCanvas);
	void static update();
};