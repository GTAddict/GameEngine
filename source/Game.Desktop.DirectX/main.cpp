#pragma once

#include "pch.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

///<summary>
/// Entry point of the application.
///</summary>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Proof of concept code. TODO: Remove when actual assignment is provided.
	const char* version = GameEngine::Library::Utils::GetEngineVersion();
	UNREFERENCED_PARAMETER(version);

	WNDCLASSEX window;
	ZeroMemory(&window, sizeof(WNDCLASSEX));

	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_HREDRAW | CS_VREDRAW;
	window.lpfnWndProc = WindowProc;
	window.hInstance = hInstance;
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hbrBackground = (HBRUSH)COLOR_WINDOW;
	window.lpszClassName = L"WindowClass";

	RegisterClassEx(&window);

	HWND hWnd;
	hWnd = CreateWindowEx(
		NULL,
		L"WindowClass",
		L"DirectX Window",
		WS_OVERLAPPEDWINDOW,
		Game::kWindowPosX,
		Game::kWindowPosY,
		Game::kWindowWidth,
		Game::kWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lparam);
}

namespace Game
{

}