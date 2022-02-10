#include "Window.hpp"
#include <iostream>

int height, width;
RGB **canvas;
Cenario *cena;

GLubyte *PixelBuffer;

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
			// obtem os dados da camera inicial
			Camera cam = cena->getCamera();
			Ponto peye3 = cam.getEye();
			Ponto plookat3 = cam.getLook_at();
			Ponto pviewup3 = cam.getUp();

			static float eye3[3] = {peye3.x(), peye3.y(), peye3.z()};
			static float lookat3[3] = {plookat3.x(), plookat3.y(), plookat3.z()};
			static float viewup3[3] = {pviewup3.x(), pviewup3.y(), pviewup3.z()};

			ImGui::InputFloat3("Eye", eye3);
			ImGui::InputFloat3("Lookat", lookat3);
			ImGui::InputFloat3("Viewup", viewup3);
			if (ImGui::Button("Atualizar camera"))
			{
				// criando camera com os dados atualizados e substituindo na cena
				Ponto new_eye {{eye3[0], eye3[1], eye3[2]}};
				Ponto new_lookat {{lookat3[0], lookat3[1], lookat3[2]}};
				Ponto new_viewup {{viewup3[0], viewup3[1], viewup3[2]}};
				Camera new_cam(new_eye, new_lookat, new_viewup);
				cena->updateCamera(new_cam);
				
				std::cout << "Camera atualizada com os novos pontos:" << std::endl;
				std::cout << "Eye: " << std::endl << "x: " << new_eye << std::endl;
				std::cout << "Lookat" << std::endl << "y: " << new_lookat << std::endl;
				std::cout << "Viewup: " << std::endl << "z: " << new_viewup << std::endl;

				// redraw();
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

Window::Window(int argc, char **argv, int setWidth, int setHeight, const char *title, RGB **setCanvas, Cenario *setCena)
{
	// Setando variáveis globais
	height = setHeight;
	width = setWidth;
	canvas = setCanvas;
	cena = setCena;

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
	PixelBuffer = new GLubyte[width * height * 3];

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