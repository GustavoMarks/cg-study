#include "Window.hpp"
#include <iostream>

Window::Window(int width, int height, const char *title)
{

	m_ShouldClose = true;
	// Inicializando glfw
	if (!glfwInit())
	{
		std::cerr << "Erro ao tentar inicializar GLFW" << std::endl;
		return;
	}

	// Configurações do Open GL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwSetErrorCallback(Window::errorCallback);

	// Criando uma janela
	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!m_Window)
	{
		std::cerr << "Erro ao tentar criar janela" << std::endl;
		return;
	}

	// Colando janela no contexto atual
	glfwMakeContextCurrent(m_Window);

	GLenum glewInitMsg = glewInit();
	if (glewInitMsg != GLEW_OK)
	{
		std::cerr << "Erro ao tentar inicializar glew" << glewGetErrorString(glewInitMsg) << std::endl;
		return;
	}

	glClearColor(0.5f, 0.5f, 1, 0);

	m_ShouldClose = false;
}

void Window::update()
{
	// Renderização
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
	glfwSwapBuffers(m_Window);

	// Chamada de fechamento de janela
	if (!m_ShouldClose)
	{
		m_ShouldClose = glfwWindowShouldClose(m_Window);
	};
}

void Window::errorCallback(int error, const char *description)
{
	std::cerr << "Erro " << error << ":" << description << std::endl;
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}