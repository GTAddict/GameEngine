#include "pch.h"
#include <GLFW/glfw3.h>

///<summary>
/// Entry point of application.
///</summary>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	// Proof of concept code. TODO: Remove when actual assignment is provided.
	const char* version = GameEngine::Library::Utils::GetEngineVersion();
	UNREFERENCED_PARAMETER(version);

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(Game::kWindowWidth, Game::kWindowHeight, "OpenGL Window", NULL, NULL);
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	return 0;
}

namespace Game
{

}