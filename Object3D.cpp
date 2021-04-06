#include "Object3D.h"

Object3D::Object3D(Graphics *graphics, Math::Vector3D pos, float sizeX, float sizeY, float sizeZ, const wchar_t* filename)
{
	this->graphics = graphics;

	m_pos = pos;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_sizeZ = sizeZ;

	m_vertexbuffer = NULL;

	m_texture = new Texture(graphics, filename);
}

Object3D::~Object3D()
{
	if (m_vertexbuffer) m_vertexbuffer->Release();
}

void Object3D::Init(void* shaderByteCode, size_t byteCodeSize)
{
	// POSITION 
	m_positionList[0] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z - m_sizeZ) };
	m_positionList[1] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z - m_sizeZ) };
	m_positionList[2] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z - m_sizeZ) };
	m_positionList[3] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z - m_sizeZ) };
	m_positionList[4] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z + m_sizeZ) };
	m_positionList[5] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z + m_sizeZ) };
	m_positionList[6] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z + m_sizeZ) };
	m_positionList[7] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z + m_sizeZ) };

	// TEXTURE POSITION
	m_texcoordList[0] = { Math::Vector2D(0.0f, 0.0f) };
	m_texcoordList[1] = { Math::Vector2D(0.0f, 1.0f) };
	m_texcoordList[2] = { Math::Vector2D(1.0f, 0.0f) };
	m_texcoordList[3] = { Math::Vector2D(1.0f, 1.0f) };

	// OVERALL VERTEX LIST
	m_vertexList[0] = { m_positionList[0], m_texcoordList[1] };
	m_vertexList[1] = { m_positionList[1], m_texcoordList[0] };
	m_vertexList[2] = { m_positionList[2], m_texcoordList[2] };
	m_vertexList[3] = { m_positionList[3], m_texcoordList[3] };

	m_vertexList[4] = { m_positionList[4], m_texcoordList[1] };
	m_vertexList[5] = { m_positionList[5], m_texcoordList[0] };
	m_vertexList[6] = { m_positionList[6], m_texcoordList[2] };
	m_vertexList[7] = { m_positionList[7], m_texcoordList[3] };

	m_vertexList[8] = { m_positionList[1], m_texcoordList[1] };
	m_vertexList[9] = { m_positionList[6], m_texcoordList[0] };
	m_vertexList[10] = { m_positionList[5], m_texcoordList[2] };
	m_vertexList[11] = { m_positionList[2], m_texcoordList[3] };

	m_vertexList[12] = { m_positionList[7], m_texcoordList[1] };
	m_vertexList[13] = { m_positionList[0], m_texcoordList[0] };
	m_vertexList[14] = { m_positionList[3], m_texcoordList[2] };
	m_vertexList[15] = { m_positionList[4], m_texcoordList[3] };

	m_vertexList[16] = { m_positionList[3], m_texcoordList[1] };
	m_vertexList[17] = { m_positionList[2], m_texcoordList[0] };
	m_vertexList[18] = { m_positionList[5], m_texcoordList[2] };
	m_vertexList[19] = { m_positionList[4], m_texcoordList[3] };

	m_vertexList[20] = { m_positionList[7], m_texcoordList[1] };
	m_vertexList[21] = { m_positionList[6], m_texcoordList[0] };
	m_vertexList[22] = { m_positionList[1], m_texcoordList[2] };
	m_vertexList[23] = { m_positionList[0], m_texcoordList[3] };

	graphics->InitVertexBuffer(&m_vertexbuffer, m_vertexList, sizeof(vertex), ARRAYSIZE(m_vertexList), shaderByteCode, byteCodeSize);
}

void Object3D::Translate(Math::Vector3D vector)
{
	m_pos.m_x += vector.m_x;
	m_pos.m_y += vector.m_y;
	m_pos.m_z += vector.m_z;

	m_positionList[0] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z - m_sizeZ) };
	m_positionList[1] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z - m_sizeZ) };
	m_positionList[2] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z - m_sizeZ) };
	m_positionList[3] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z - m_sizeZ) };

	m_positionList[4] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z + m_sizeZ) };
	m_positionList[5] = { Math::Vector3D(m_pos.m_x + m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z + m_sizeZ) };
	m_positionList[6] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y + m_sizeY, m_pos.m_z + m_sizeZ) };
	m_positionList[7] = { Math::Vector3D(m_pos.m_x - m_sizeX, m_pos.m_y - m_sizeY, m_pos.m_z + m_sizeZ) };
}

void Object3D::UpdateVertices()
{
	m_vertexList[0] = { m_positionList[0], m_texcoordList[1] };
	m_vertexList[1] = { m_positionList[1], m_texcoordList[0] };
	m_vertexList[2] = { m_positionList[2], m_texcoordList[2] };
	m_vertexList[3] = { m_positionList[3], m_texcoordList[3] };

	m_vertexList[4] = { m_positionList[4], m_texcoordList[1] };
	m_vertexList[5] = { m_positionList[5], m_texcoordList[0] };
	m_vertexList[6] = { m_positionList[6], m_texcoordList[2] };
	m_vertexList[7] = { m_positionList[7], m_texcoordList[3] };

	m_vertexList[8] = { m_positionList[1], m_texcoordList[1] };
	m_vertexList[9] = { m_positionList[6], m_texcoordList[0] };
	m_vertexList[10] = { m_positionList[5], m_texcoordList[2] };
	m_vertexList[11] = { m_positionList[2], m_texcoordList[3] };

	m_vertexList[12] = { m_positionList[7], m_texcoordList[1] };
	m_vertexList[13] = { m_positionList[0], m_texcoordList[0] };
	m_vertexList[14] = { m_positionList[3], m_texcoordList[2] };
	m_vertexList[15] = { m_positionList[4], m_texcoordList[3] };

	m_vertexList[16] = { m_positionList[3], m_texcoordList[1] };
	m_vertexList[17] = { m_positionList[2], m_texcoordList[0] };
	m_vertexList[18] = { m_positionList[5], m_texcoordList[2] };
	m_vertexList[19] = { m_positionList[4], m_texcoordList[3] };

	m_vertexList[20] = { m_positionList[7], m_texcoordList[1] };
	m_vertexList[21] = { m_positionList[6], m_texcoordList[0] };
	m_vertexList[22] = { m_positionList[1], m_texcoordList[2] };
	m_vertexList[23] = { m_positionList[0], m_texcoordList[3] };
}

void Object3D::Render()
{
	UpdateVertices();
	graphics->SetTexturePS(m_texture->GetShaderResourceView());
	graphics->SetVertexBuffer(m_vertexbuffer);
	graphics->UpdateVertexBuffer(&m_vertexbuffer, m_vertexList, sizeof(vertex)*24);
}

bool Object3D::CollideWithPoint(Math::Vector3D p)
{
	return (p.m_x >= m_vertexList[0].pos.m_x && p.m_x <= m_vertexList[3].pos.m_x) && 
		   (p.m_y >= m_vertexList[0].pos.m_y && p.m_y <= m_vertexList[1].pos.m_y) && 
		   (p.m_z >= m_vertexList[0].pos.m_z && p.m_z <= m_vertexList[7].pos.m_z);
}

Math::Vector3D Object3D::GetPos()
{
	return m_pos;
}

Math::Vector3D Object3D::GetSize()
{
	return Math::Vector3D(m_sizeX, m_sizeY, m_sizeZ);
}