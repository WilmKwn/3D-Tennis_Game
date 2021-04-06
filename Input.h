#pragma once

#include <Windows.h>
#define WIN32_MEAN_AND_LEAN

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

class Input
{
public:
	Input();
	~Input();

	static bool GetKeyDown(int vk_code);

	static float GetMouseX();
	static float GetMouseY();

	static bool GetMouseLeftClick();
	static bool GetMouseRightClick();

	static void SetMouseLeftClick(bool click);
	static void SetMouseRightClick(bool click);

	static void SetMouseToCenter(float width, float height);

	// FIX IN WINDOW.CPP
	static void SetMouseScrollDelta(int delta);
	static int GetMouseScrollDelta();

private:
	static float m_mouseX;
	static float m_mouseY;

	static bool m_mouseLeftClick;
	static bool m_mouseRightClick;

	static int m_mouseScrollDelta;
};