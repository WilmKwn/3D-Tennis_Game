#pragma once

#include "Object3D.h"
#include "Input.h"
#include "Window.h"

class Game
{
public:
	Game(Graphics *graphics);
	~Game();

	__declspec(align(16))
		struct constantBuffer
	{
		Math::Matrix4x4 m_worldMatrix;
		Math::Matrix4x4 m_viewMatrix;
		Math::Matrix4x4 m_projectionMatrix;
		unsigned int time;
	};

	void Init();
	void Update(Window *window);

	bool InsideSwingRange(Math::Vector3D camPos);

private:
	Graphics *graphics;

	constantBuffer c;

	Object3D *court;
	Object3D *net;
	Object3D *ball;

	int cubeIndexList[36] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15 ,12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	float oldMouseX;
	float oldMouseY;
	float mouseDeltaX;
	float mouseDeltaY;

	float forward;
	float sideway;

	bool jump;
	bool jumpDirection;
	float jumpVelocity;
	float gravity;

	float groundY;

	bool bounceOnce;

	bool gameOver;

	int swingDelayCounter;

	Math::Vector3D ballVelocity;

	Math::Matrix4x4 oldWorldCamera;
};