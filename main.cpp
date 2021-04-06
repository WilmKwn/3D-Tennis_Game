#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	Window *window = new Window();
	window->Init(800, 600, 0, 0, hInstance);

	Graphics *graphics = new Graphics();
	graphics->Init();
	graphics->InitSwapChain(window->GetHandle(), window->GetWindowSize().first, window->GetWindowSize().second);
	
	Game *game = new Game(graphics);
	game->Init();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		game->Update(window);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}