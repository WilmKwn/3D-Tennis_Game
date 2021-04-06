#include "Input.h"

float Input::m_mouseX = 0;
float Input::m_mouseY = 0;

bool Input::m_mouseLeftClick = false;
bool Input::m_mouseRightClick = false;

int Input::m_mouseScrollDelta = 0;

Input::Input() {}
Input::~Input() {}

bool Input::GetKeyDown(int vk_code)
{
	return (GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0;
}

float Input::GetMouseX()
{
	POINT p;
	GetCursorPos(&p);
	return (float)p.x;
}

float Input::GetMouseY()
{
	POINT p;
	GetCursorPos(&p);
	return (float)p.y;
}

bool Input::GetMouseLeftClick()
{
	return m_mouseLeftClick;
}

bool Input::GetMouseRightClick()
{
	return m_mouseRightClick;
}

void Input::SetMouseLeftClick(bool click)
{
	m_mouseLeftClick = click;
}

void Input::SetMouseRightClick(bool click)
{
	m_mouseRightClick = click;
}

void Input::SetMouseToCenter(float width, float height)
{
	SetCursorPos((int)width / 2, (int)height / 2);
}

void Input::SetMouseScrollDelta(int delta)
{
	m_mouseScrollDelta = delta;
}

int Input::GetMouseScrollDelta()
{
	return m_mouseScrollDelta;
}