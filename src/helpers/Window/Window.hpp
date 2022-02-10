#include <GL/glut.h>
#include "../../components/RayCasting/RayCasting.hpp"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_glut.h"
#include "../../imgui/imgui_impl_opengl2.h"
class Window
{
public:
	Window(int argc, char **argv, int width, int height, const char *title, RGB **setCanvas, Cenario *setCena, float setD, int setH, int setW);
	void static update();
};