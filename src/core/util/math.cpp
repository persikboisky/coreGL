#include "math.hpp"

using namespace math;

#pragma region Vecotr2

Vector2::Vector2(float x, float y) : x(x), y(y)
{

}

Vector2 Vector2::operator + (Vector2 vector2)
{
	return Vector2(
		this->x + vector2.x,
		this->y + vector2.y
	);
}

Vector2 Vector2::operator - (Vector2 vector2)
{
	return Vector2(
		this->x - vector2.x,
		this->y - vector2.y
		);
}

Vector2 Vector2::operator * (Vector2 vector2)
{
	return Vector2(
		this->x * vector2.x,
		this->y * vector2.y
	);
}

Vector2 Vector2::operator / (Vector2 vector2)
{
	return Vector2(
		this->x / vector2.x,
		this->y / vector2.y
	);
}

#pragma endregion Vector2

#pragma region Vecotr3

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{}

Vector3::Vector3(Vector2 vector2, float z) : x(vector2.x), y(vector2.y), z(z)
{}

Vector3::Vector3(float x, Vector2 vector2) : x(x), y(vector2.y), z(vector2.x)
{}

Vector3 Vector3::operator + (Vector3 vector3)
{
	return Vector3(
		this->x + vector3.x, 
		this->y + vector3.y,
		this->z + vector3.z
	);
}

Vector3 Vector3::operator - (Vector3 vector3)
{
	return Vector3(
		this->x - vector3.x,
		this->y - vector3.y,
		this->z - vector3.z
	);
}

Vector3 Vector3::operator * (Vector3 vector3)
{
	return Vector3(
		this->x * vector3.x,
		this->y * vector3.y,
		this->z * vector3.z
	);
}

Vector3 Vector3::operator / (Vector3 vector3)
{
	return Vector3(
		this->x / vector3.x,
		this->y / vector3.y,
		this->z / vector3.z
	);
}

#pragma endregion Vector3

#pragma region Vecotr4

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{ }

Vector4::Vector4(float x, Vector3 vector3) : x(x), y(vector3.x), z(vector3.y), w(vector3.z)
{ }

Vector4::Vector4(Vector3 vector3, float w) : x(vector3.x), y(vector3.y), z(vector3.z), w(w)
{ }

Vector4::Vector4(Vector2 vector2_1, Vector2 vector2_2) : x(vector2_1.x), y(vector2_1.y), z(vector2_2.x), w(vector2_2.y)
{ }

Vector4::Vector4(Vector2 vector2, float z, float w) : x(vector2.x), y(vector2.y), z(z), w(w)
{ }

Vector4::Vector4(float x, Vector2 vector2, float w) : x(x), y(vector2.x), z(vector2.y), w(w)
{ }

Vector4::Vector4(float x, float y, Vector2 vector2) : x(x), y(y), z(vector2.x), w(vector2.y)
{ }

Vector4 Vector4::operator + (Vector4 vector4)
{
	return Vector4(
		this->x + vector4.x,
		this->y + vector4.y,
		this->z + vector4.z,
		this->w + vector4.w
	);
}

Vector4 Vector4::operator - (Vector4 vector4)
{
	return Vector4(
		this->x - vector4.x,
		this->y - vector4.y,
		this->z - vector4.z,
		this->w - vector4.w
	);
}

Vector4 Vector4::operator * (Vector4 vector4)
{
	return Vector4(
		this->x * vector4.x,
		this->y * vector4.y,
		this->z * vector4.z,
		this->w * vector4.w
	);
}

Vector4 Vector4::operator / (Vector4 vector4)
{
	return Vector4(
		this->x / vector4.x,
		this->y / vector4.y,
		this->z / vector4.z,
		this->w / vector4.w
	);
}

#pragma endregion Vector4