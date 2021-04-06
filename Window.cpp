#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_MOUSEWHEEL:
		Input::SetMouseScrollDelta(GET_WHEEL_DELTA_WPARAM(wp));
		return 0;
	case WM_LBUTTONDOWN:
		Input::SetMouseLeftClick(true);
		return 0;
	case WM_LBUTTONUP:
		Input::SetMouseLeftClick(false);
		return 0;
	case WM_RBUTTONDOWN:
		Input::SetMouseRightClick(true);
		return 0;
	case WM_RBUTTONUP:
		Input::SetMouseRightClick(false);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void Window::Init(int width, int height, int x, int y, HINSTANCE hInstance)
{
	WNDCLASSEX wcex = { 0 };
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hInstance;
	wcex.cbWndExtra = 0;
	wcex.cbClsExtra = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "o";
	wcex.lpfnWndProc = WndProc;
	RegisterClassEx(&wcex);

	m_handle = CreateWindowEx(NULL, "o", "ight", WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, width, height, NULL, NULL, hInstance, NULL);
}

HWND Window::GetHandle()
{
	return this->m_handle;
}

std::pair<int, int> Window::GetWindowSize()
{
	RECT rect;
	GetClientRect(m_handle, &rect);
	return std::make_pair(rect.right - rect.left, rect.bottom - rect.top);
}