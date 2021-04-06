#include "Math.h"

Math::Math() {}
Math::~Math() {}

///////////////// VECTOR3D CLASS /////////////////////

Math::Vector2D::Vector2D()
{
	m_x = 0;
	m_y = 0;
}

Math::Vector2D::Vector2D(float x, float y)
{
	m_x = x;
	m_y = y;
}

Math::Vector2D::Vector2D(const Vector2D &vector)
{
	m_x = vector.m_x;
	m_y = vector.m_y;
}

Math::Vector2D::~Vector2D()
{
}

///////////////// VECTOR3D CLASS /////////////////////

Math::Vector3D::Vector3D()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
}
Math::Vector3D::Vector3D(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}
Math::Vector3D::Vector3D(const Vector3D &vector)
{
	m_x = vector.m_x;
	m_y = vector.m_y;
	m_z = vector.m_z;
}
Math::Vector3D::~Vector3D()
{
}

Math::Vector3D Math::Vector3D::Lerp(const Vector3D &startVector, const Vector3D &endVector, float delta)
{
	Vector3D outputVector;
	outputVector.m_x = startVector.m_x * (1.0f - delta) + endVector.m_x * delta;
	outputVector.m_y = startVector.m_y * (1.0f - delta) + endVector.m_y * delta;
	outputVector.m_z = startVector.m_z * (1.0f - delta) + endVector.m_z * delta;
	return outputVector;
}

Math::Vector3D Math::Vector3D::operator * (float num)
{
	return Vector3D(m_x * num, m_y * num, m_z * num);
}

Math::Vector3D Math::Vector3D::operator + (Vector3D vector)
{
	return  Vector3D(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
}

///////////////// VECTOR4D CLASS /////////////////////

Math::Vector4D::Vector4D()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_w = 0;
}
Math::Vector4D::Vector4D(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}
Math::Vector4D::Vector4D(const Vector4D &vector)
{
	m_x = vector.m_x;
	m_y = vector.m_y;
	m_z = vector.m_z;
	m_w = vector.m_w;
}
Math::Vector4D::~Vector4D()
{
}

void Math::Vector4D::Cross(Vector4D &v1, Vector4D &v2, Vector4D &v3)
{
	m_x = v1.m_y * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) + v1.m_w * (v2.m_y * v3.m_z - v2.m_z *v3.m_y);
	m_y = -(v1.m_x * (v2.m_z * v3.m_w - v3.m_z * v2.m_w) - v1.m_z * (v2.m_x * v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_z - v3.m_x * v2.m_z));
	m_z = v1.m_x * (v2.m_y * v3.m_w - v3.m_y * v2.m_w) - v1.m_y * (v2.m_x *v3.m_w - v3.m_x * v2.m_w) + v1.m_w * (v2.m_x * v3.m_y - v3.m_x * v2.m_y);
	m_w = -(v1.m_x * (v2.m_y * v3.m_z - v3.m_y * v2.m_z) - v1.m_y * (v2.m_x * v3.m_z - v3.m_x *v2.m_z) + v1.m_z * (v2.m_x * v3.m_y - v3.m_x * v2.m_y));
}

///////////////// MATRIX4X4 CLASS ////////////////////

Math::Matrix4x4::Matrix4x4()
{
}

Math::Matrix4x4::~Matrix4x4()
{
}

void Math::Matrix4x4::SetMatrix(const Matrix4x4 &matrix)
{
	memcpy(m_matrix, matrix.m_matrix, sizeof(float) * 16);
}

void Math::Matrix4x4::SetIdentityMatrix()
{
	memset(&m_matrix, 0, sizeof(float) * 16);
	m_matrix[0][0] = 1;
	m_matrix[1][1] = 1;
	m_matrix[2][2] = 1;
	m_matrix[3][3] = 1;
}

void Math::Matrix4x4::SetTranslationMatrix(const Vector3D &vector)
{
	m_matrix[3][0] = vector.m_x;
	m_matrix[3][1] = vector.m_y;
	m_matrix[3][2] = vector.m_z;
}

void Math::Matrix4x4::SetScaleMatrix(const Vector3D &vector)
{
	m_matrix[0][0] = vector.m_x;
	m_matrix[1][1] = vector.m_y;
	m_matrix[2][2] = vector.m_z;
}

void Math::Matrix4x4::SetRotationX(float theta)
{
	m_matrix[1][1] = cos(theta);
	m_matrix[1][2] = sin(theta);
	m_matrix[2][1] = -sin(theta);
	m_matrix[2][2] = cos(theta);
}

void Math::Matrix4x4::SetRotationY(float theta)
{
	m_matrix[0][0] = cos(theta);
	m_matrix[0][2] = -sin(theta);
	m_matrix[2][0] = sin(theta);
	m_matrix[2][2] = cos(theta);
}

void Math::Matrix4x4::SetRotationZ(float theta)
{
	m_matrix[0][0] = cos(theta);
	m_matrix[0][1] = sin(theta);
	m_matrix[1][0] = -sin(theta);
	m_matrix[1][1] = cos(theta);
}

void Math::Matrix4x4::SetPerspectiveLHMatrix(float fovDegrees, float aspectRatio, float zNear, float zFar)
{
	SetIdentityMatrix();
	float fovRadians = fovDegrees * (3.14159 / 180.0f);
	float yScale = 1.0f / tanf(fovRadians / 2.0f);
	float xScale = yScale / aspectRatio;
	m_matrix[0][0] = xScale;
	m_matrix[1][1] = yScale;
	m_matrix[2][2] = zFar / (zFar - zNear);
	m_matrix[2][3] = 1.0f;
	m_matrix[3][2] = (-zNear * zFar) / (zFar - zNear);
}

void Math::Matrix4x4::SetOrthoLHMatrix(float width, float height, float nearPlane, float farPlane)
{
	SetIdentityMatrix();
	m_matrix[0][0] = 2.0f / width;
	m_matrix[1][1] = 2.0f / height;
	m_matrix[2][2] = 1.0f / (farPlane - nearPlane);
	m_matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
}

void Math::Matrix4x4::SetInverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4D v, vec[3];
	float det = 0.0f;

	det = GetDeterminant();
	if (!det) return;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].m_x = (this->m_matrix[j][0]);
				vec[a].m_y = (this->m_matrix[j][1]);
				vec[a].m_z = (this->m_matrix[j][2]);
				vec[a].m_w = (this->m_matrix[j][3]);
			}
		}
		v.Cross(vec[0], vec[1], vec[2]);

		out.m_matrix[0][i] = pow(-1.0f, i) * v.m_x / det;
		out.m_matrix[1][i] = pow(-1.0f, i) * v.m_y / det;
		out.m_matrix[2][i] = pow(-1.0f, i) * v.m_z / det;
		out.m_matrix[3][i] = pow(-1.0f, i) * v.m_w / det;
	}

	SetMatrix(out);
}

void Math::Matrix4x4::operator*=(const Matrix4x4 matrix)
{
	Matrix4x4 output;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			output.m_matrix[i][j] = m_matrix[i][0] * matrix.m_matrix[0][j] + m_matrix[i][1] * matrix.m_matrix[1][j] + 
									m_matrix[i][2] * matrix.m_matrix[2][j] + m_matrix[i][3] * matrix.m_matrix[3][j];
		}
	}
	memcpy(m_matrix, output.m_matrix, sizeof(float) * 16);
}

float Math::Matrix4x4::GetDeterminant()
{
	Vector4D minor, v1, v2, v3;
	float det;

	v1 = Vector4D(this->m_matrix[0][0], this->m_matrix[1][0], this->m_matrix[2][0], this->m_matrix[3][0]);
	v2 = Vector4D(this->m_matrix[0][1], this->m_matrix[1][1], this->m_matrix[2][1], this->m_matrix[3][1]);
	v3 = Vector4D(this->m_matrix[0][2], this->m_matrix[1][2], this->m_matrix[2][2], this->m_matrix[3][2]);


	minor.Cross(v1, v2, v3);
	det = -(this->m_matrix[0][3] * minor.m_x + this->m_matrix[1][3] * minor.m_y + this->m_matrix[2][3] * minor.m_z +
		this->m_matrix[3][3] * minor.m_w);
	return det;
}

Math::Vector3D Math::Matrix4x4::GetDirectionX()
{
	return Vector3D(m_matrix[0][0], m_matrix[0][1], m_matrix[0][2]);
}

Math::Vector3D Math::Matrix4x4::GetDirectionY()
{
	return Vector3D(m_matrix[1][0], m_matrix[1][1], m_matrix[1][2]);
}

Math::Vector3D Math::Matrix4x4::GetDirectionZ()
{
	return Vector3D(m_matrix[2][0], m_matrix[2][1], m_matrix[2][2]);
}

Math::Vector3D Math::Matrix4x4::GetTranslation()
{
	return Vector3D(m_matrix[3][0], m_matrix[3][1], m_matrix[3][2]);
}