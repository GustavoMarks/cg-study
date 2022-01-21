#include "Window.hpp"
#include <iostream>

Window::Window(int argc, char **argv, int width, int height, const char *title)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);

	glutDisplayFunc(update);
	glutMainLoop();
}

void Window::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}