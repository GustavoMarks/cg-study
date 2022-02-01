#include "Window.hpp"
#include <iostream>

int height, width;
RGB **canvas;

Window::Window(int argc, char **argv, int setWidth, int setHeight, const char *title, RGB **setCanvas)
{
	// Setando variáveis globais
	height = setHeight;
	width = setWidth;
	canvas = setCanvas;

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
	// Criando framebuffer a partir de um canvas
	GLubyte *PixelBuffer = new GLubyte[width * height * 3];

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			int position = (x + y * width) * 3;
			PixelBuffer[position] = canvas[x][height - y].r;
			PixelBuffer[position + 1] = canvas[x][height - y].g;
			PixelBuffer[position + 2] = canvas[x][height - y].b;
		}
	}

	glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, PixelBuffer);
	glutSwapBuffers();
}