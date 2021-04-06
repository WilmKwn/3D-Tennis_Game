#include "Game.h"

Game::Game(Graphics *graphics)
{
	this->graphics = graphics;
}

Game::~Game()
{

}

void Game::Init()
{
	const wchar_t* courtTexture = L"C:\\Users\\willi\\source\\repos\\Direct3D_11\\Direct3D_11\\Assets\\Textures\\tennisCourt.jpg";
	const wchar_t* netTexture = L"C:\\Users\\willi\\source\\repos\\Direct3D_11\\Direct3D_11\\Assets\\Textures\\net.jpg";
	const wchar_t* ballTexture = L"C:\\Users\\willi\\source\\repos\\Direct3D_11\\Direct3D_11\\Assets\\Textures\\ball.jpg";
	court = new Object3D(graphics, Math::Vector3D(0.0f, 0.0f, 0.0f), 1.8f, 0.1f, 3.9f, courtTexture);
	net = new Object3D(graphics, Math::Vector3D(0.0f, court->GetPos().m_y + court->GetSize().m_y + 0.175, 0.0f), court->GetSize().m_x, 0.175f, 0.05f, netTexture);
	ball = new Object3D(graphics, Math::Vector3D(0.0f, net->GetPos().m_x + 0.5f, 0.0f), 0.03f, 0.03f, 0.03f, ballTexture);

	graphics->InitIndexBuffer(cubeIndexList, ARRAYSIZE(cubeIndexList));

	void* shaderByteCode = NULL;
	size_t shaderByteCodeSize = 0;

	graphics->CompileVertexShader(L"C:/Users/willi/source/repos/Direct3D_11/Direct3D_11/VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderByteCodeSize);
	graphics->InitVertexShader(shaderByteCode, shaderByteCodeSize);
	
	court->Init(shaderByteCode, shaderByteCodeSize);
	net->Init(shaderByteCode, shaderByteCodeSize);
	ball->Init(shaderByteCode, shaderByteCodeSize);

	graphics->CompilePixelShader(L"C:/Users/willi/source/repos/Direct3D_11/Direct3D_11/PixelShader.hlsl", "psmain", &shaderByteCode, &shaderByteCodeSize);
	graphics->InitPixelShader(shaderByteCode, shaderByteCodeSize);

	c.time = 0;
	graphics->InitConstantBuffer(&c, sizeof(constantBuffer));

	oldMouseX = Input::GetMouseX();
	oldMouseY = Input::GetMouseY();

	mouseDeltaX = 0.0f;
	mouseDeltaY = 0.0f;

	forward = 0.0f;
	sideway = 0.0f;

	jump = false;
	jumpDirection = 1;
	jumpVelocity = 0.1f;
	gravity = 0.005f;

	groundY = 0.7f;

	bounceOnce = false;

	gameOver = false;

	swingDelayCounter = 0;

	ballVelocity = Math::Vector3D(0.0f, 0.0f, 0.1f);

	oldWorldCamera.SetTranslationMatrix(Math::Vector3D(0.0f, 0.0f, -2.0f));
}

void Game::Update(Window *window)
{
	graphics->ClearRenderTarget(0.2f, 0.2f, 0.2f, 1.0f);
	graphics->SetViewportSize(window->GetWindowSize().first, window->GetWindowSize().second);
	c.time = GetTickCount();




	if (!gameOver) {
		mouseDeltaX += Input::GetMouseX() - oldMouseX;
		mouseDeltaY += Input::GetMouseY() - oldMouseY;

		if (!Input::GetKeyDown(VK_ESCAPE)) Input::SetMouseToCenter((float)window->GetWindowSize().first, (float)window->GetWindowSize().second);

		c.m_worldMatrix.SetIdentityMatrix();

		Math::Matrix4x4 temp;
		Math::Matrix4x4 worldCamera;
		worldCamera.SetIdentityMatrix();

		temp.SetIdentityMatrix();
		temp.SetRotationX(mouseDeltaY * 0.005f);
		worldCamera *= temp;

		temp.SetIdentityMatrix();
		temp.SetRotationY(mouseDeltaX*0.005f);
		worldCamera *= temp;

		oldMouseX = Input::GetMouseX();
		oldMouseY = Input::GetMouseY();
		if (Input::GetKeyDown(VK_W)) forward = 1.0f;
		else if (Input::GetKeyDown(VK_S)) forward = -1.0f;
		else forward = 0.0f;
		if (Input::GetKeyDown(VK_D)) sideway = 1.0f;
		else if (Input::GetKeyDown(VK_A)) sideway = -1.0f;
		else sideway = 0.0f;

		if (Input::GetKeyDown(VK_SPACE)) jump = true;

		Math::Vector3D newPos = oldWorldCamera.GetTranslation() + worldCamera.GetDirectionZ() * (forward * 0.05f);
		newPos = newPos + worldCamera.GetDirectionX() * (sideway * 0.05f);

		if (jump) {
			newPos.m_y += jumpVelocity;
			jumpVelocity -= gravity;
			if (jumpVelocity <= 0)
				jumpDirection = 0;
			else
				jumpDirection = 1;
			if (newPos.m_y <= groundY + 0.2f) {
				jumpVelocity = 0.1f;
				jump = false;
			}
		}
		else {
			newPos.m_y = groundY + 0.2f;
		}
		ballVelocity.m_y -= gravity;
		if (ball->GetPos().m_y <= court->GetPos().m_y + court->GetSize().m_y && !bounceOnce) {
			ball->Translate(Math::Vector3D(0.0f, court->GetPos().m_y + court->GetSize().m_y, 0.0f));
			ballVelocity.m_y = 0.1f;
			ballVelocity.m_x = 0.0f;
			bounceOnce = true;
		}
		else if (ball->GetPos().m_y <= court->GetPos().m_y + court->GetSize().m_y &&bounceOnce) {
			gameOver = true;
		}
		if (ball->GetPos().m_z >= court->GetPos().m_z + court->GetSize().m_z) {
			ballVelocity.m_z = -0.15f;
			ballVelocity.m_y = 0.05f;
			ballVelocity.m_x = 0.0f;
			bounceOnce = false;
		}

		if (swingDelayCounter > 0) {
			swingDelayCounter++;
			if (swingDelayCounter >= 60) {
				swingDelayCounter = 0;
			}
		}
		if (Input::GetMouseLeftClick() && InsideSwingRange(newPos) && swingDelayCounter == 0) {
			swingDelayCounter = 1;
			ballVelocity = ballVelocity + worldCamera.GetDirectionZ() * 0.05f;
			ballVelocity.m_z = 0.2f;
			ballVelocity.m_y = 0.05f;
			bounceOnce = false;
		}
		ball->Translate(ballVelocity);

		worldCamera.SetTranslationMatrix(newPos);

		oldWorldCamera = worldCamera;

		worldCamera.SetInverse();

		c.m_viewMatrix = worldCamera;
		c.m_projectionMatrix.SetPerspectiveLHMatrix(60.0f, (float)window->GetWindowSize().first / (float)window->GetWindowSize().second, 0.0f, 100.0f);
		graphics->UpdateConstantBuffer(&c);





		graphics->SetConstantBuffer();
		graphics->SetVertexShader();
		graphics->SetPixelShader();

	}
	////////// DRAW OBJECTS ///////////////
	graphics->SetIndexBuffer();

	court->Render();
	graphics->DrawIndexedTriangleList(ARRAYSIZE(cubeIndexList), 0, 0);
	net->Render();
	graphics->DrawIndexedTriangleList(ARRAYSIZE(cubeIndexList), 0, 0);
	ball->Render();
	graphics->DrawIndexedTriangleList(ARRAYSIZE(cubeIndexList), 0, 0);

	graphics->PresentSwapChain(true);
}

bool Game::InsideSwingRange(Math::Vector3D camPos)
{
	return (ball->GetPos().m_z <= camPos.m_z + 0.5f && ball->GetPos().m_z >= camPos.m_z - 0.5f && ball->GetPos().m_x <= camPos.m_x + 0.5f && ball->GetPos().m_x >= camPos.m_x - 0.5f);
}