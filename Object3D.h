#pragma once

#include "Math.h"
#include "Texture.h"

struct vertex
{
	Math::Vector3D pos;
	Math::Vector2D texcoord;
};

class Object3D
{
public:
	Object3D(Graphics *graphics, Math::Vector3D pos, float sizeX, float sizeY, float sizeZ, const wchar_t* filename);
	~Object3D();

	void Init(void* shaderByteCode, size_t byteCodeSize);

	void UpdateVertices();
	void Translate(Math::Vector3D vector);
	
	void Render();

	bool CollideWithPoint(Math::Vector3D p);

	Math::Vector3D GetPos();

	Math::Vector3D GetSize();

private:
	Graphics *graphics;

	ID3D11Buffer *m_vertexbuffer;

	Math::Vector3D m_pos;

	vertex m_vertexList[24];
	Math::Vector3D m_positionList[8];
	Math::Vector2D m_texcoordList[4];

	float m_sizeX;
	float m_sizeY;
	float m_sizeZ;

	Texture *m_texture;
};