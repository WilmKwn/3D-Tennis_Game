#pragma once

#include <memory>

class Math
{
public:
	Math();
	~Math();

	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(float x, float y);
		Vector2D(const Vector2D &vector);
		~Vector2D();

		float m_x, m_y;
	};

	class Vector3D
	{
	public:
		Vector3D();
		Vector3D(float x, float y, float z);
		Vector3D(const Vector3D &vector);
		~Vector3D();

		static Vector3D Lerp(const Vector3D &startVector, const Vector3D &endVector, float delta);

		Vector3D operator * (float num);
		Vector3D operator + (Vector3D vector);

		float m_x, m_y, m_z;
	};

	class Vector4D
	{
	public:
		Vector4D();
		Vector4D(float x, float y, float z, float w);
		Vector4D(const Vector4D &vector);
		~Vector4D();

		// COPY PASTED //
		void Cross(Vector4D &v1, Vector4D &v2, Vector4D &v3);

		float m_x, m_y, m_z, m_w;
	};

	class Matrix4x4
	{
	public:
		Matrix4x4();
		~Matrix4x4();

		void SetMatrix(const Matrix4x4 &matrix);

		void SetIdentityMatrix();
		void SetTranslationMatrix(const Vector3D &vector);
		void SetScaleMatrix(const Vector3D &vector);
		void SetRotationX(float theta);
		void SetRotationY(float theta);
		void SetRotationZ(float theta);

		void SetPerspectiveLHMatrix(float fovDegrees, float aspectRatio, float zNear, float zFar);
		void SetOrthoLHMatrix(float width, float height, float nearPlane, float farPlane);

		// COPY PASTED //
		void SetInverse();
		float GetDeterminant();
		/////////////////

		Vector3D GetDirectionX();
		Vector3D GetDirectionY();
		Vector3D GetDirectionZ();
		Vector3D GetTranslation();

		void operator *= (const Matrix4x4 matrix);

	private:
		float m_matrix[4][4];
	};
private:

};