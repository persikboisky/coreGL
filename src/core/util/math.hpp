#pragma once

namespace math
{
    struct Vector2;
	struct Vector3;
	struct Vector4;
}

struct math::Vector2 final
{
	float x;
	float y;

	Vector2(float x = 0, float y = 0);

	Vector2 operator + (Vector2 vector2);
	Vector2 operator - (Vector2 vector2);
	Vector2 operator * (Vector2 vector2);
	Vector2 operator / (Vector2 vector2);
};

struct math::Vector3 final
{
	float x;
	float y;
	float z;

	Vector3(float x = 0, float y = 0, float z = 0);
	Vector3(Vector2 vector, float z = 0);
	Vector3(float x, Vector2 vector);

	Vector3 operator + (Vector3 vector3);
	Vector3 operator - (Vector3 vector3);
	Vector3 operator * (Vector3 vector3);
	Vector3 operator / (Vector3 vector3);
};

struct math::Vector4 final
{
	float x;
	float y;
	float z;
	float w;

	Vector4(float x = 0, float y = 0, float z = 0, float w = 1);
	Vector4(float x, Vector3 vector3 = Vector3());
	Vector4(Vector3 vector3, float w = 1);
	Vector4(Vector2 vector2_1, Vector2 vector2_2);
	Vector4(Vector2 vector2, float z = 0, float w = 1);
	Vector4(float x, Vector2 vector2, float w = 1);
	Vector4(float x, float y, Vector2 vector2);

	Vector4 operator + (Vector4 vector4);
	Vector4 operator - (Vector4 vector4);
	Vector4 operator * (Vector4 vector4);
	Vector4 operator / (Vector4 vector4);
};