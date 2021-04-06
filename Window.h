#pragma once

#include "Input.h"

#include <Windows.h>
#include <iostream>

#define WIN32_LEAN_AND_MEAN

class Window
{
public:
	Window();
	~Window();

	void Init(int width, int height, int x, int y, HINSTANCE hInstance);

	HWND GetHandle();

	std::pair<int, int> GetWindowSize();

private:
	HWND m_handle;
};