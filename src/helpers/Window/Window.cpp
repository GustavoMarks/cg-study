#include "Window.hpp"
#include <iostream>

int height, width;
RGB **canvas;

static float observerf3[3] = {0.0f, 180.0f, 355.0f};
static float lookatf3[3] = {300.0f, 160.0f, 0.0f};
static float viewupf3[3] = {0.0f, 181.0f, 355.0f};

static void display_gui()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoSavedSettings;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

	ImGui::Begin("Cenario", NULL, window_flags);
	if (ImGui::BeginTabBar("Main tab bar"))
	{
		/* Propriedades de camera */
		if (ImGui::BeginTabItem("Camera"))
		{
			ImGui::InputFloat3("Eye", observerf3);
			ImGui::InputFloat3("Lookat", lookatf3);
			ImGui::InputFloat3("Viewup", viewupf3);
			if (ImGui::Button("Atualizar camera"))
			{
				// setar propriedades da camera
			}
			
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

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

	// Iniciando contexto
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();

	// Setando binds com GLUT
	ImGui_ImplGLUT_Init();
	ImGui_ImplGLUT_InstallFuncs();
	ImGui_ImplOpenGL2_Init();

	glutMainLoop();

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();
}

void Window::update()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();
	display_gui();
	ImGui::Render();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Criando framebuffer a partir de um canvas
	GLubyte *PixelBuffer = new GLubyte[width * height * 3];

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			int position = (x + y * width) * 3;
			PixelBuffer[position] = canvas[height - y - 1][x].r;
			PixelBuffer[position + 1] = canvas[height - y - 1][x].g;
			PixelBuffer[position + 2] = canvas[height - y - 1][x].b;
		}
	}

	glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, PixelBuffer);

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glutSwapBuffers();
	glutPostRedisplay();
}