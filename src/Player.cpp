#define PI 3.14

#include "Player.h"
#include "core/graphics/Camera.h"
#include "core/graphics/shader.h"
#include <iostream>

const float SPEED_MOUSE = 1.5f;
const float SPEED_CAMERA = 0.02f;
const float acceleration = 2.0f;

float deltaX = 0;
float deltaY = 0;
float moveX = 0.0f;
float moveZ = 0.0f;

void Player::review(int w_width, int w_height, double mouseX, double mouseY)
{
	deltaX += 1 / (float)w_width * -(float)mouseX;
	deltaY += 1 / (float)w_height * -(float)mouseY;

	if (deltaX >= PI * 2) deltaX -= PI * 2;
	if (deltaX <= -PI * 2) deltaX += PI * 2;

	if (deltaY >= PI * 2) deltaY -= PI * 2;
	if (deltaY <= -PI * 2) deltaY += PI * 2;

	cam->resetRotate();
	cam->rotate(deltaY, deltaX, 0.0f);

	//std::cout << deltaX << " : " << deltaY << std::endl;
}

Player::Player(float x, float y, float z, float fov) : pos(x, y, z)
{
	this->cam = new Camera(x, y, z, fov);
}

Player::~Player()
{
	delete this->cam;
}

void Player::render(const char* nameUniformView, const char* nameUniformProj, int w_width, int w_height, double mouseX, double mouseY)
{
	this->review(w_width, w_height, mouseX, mouseY);
	shader::UniformMat4(cam->getProj(w_width, w_height) * cam->getView(), "view_proj");
	//shader::UniformMat4(cam->getProj(w_width, w_height), nameUniformProj);
	//shader::UniformMat4(cam->getView(), nameUniformView);
}

void Player::move(bool keyArray[])
{
	if (deltaX >= 0)
	{
		if (deltaX <= PI / 2)
		{
			moveX = (deltaX / 157.0f) * acceleration;
			moveZ = (0.01f - deltaX / 157.0f) * acceleration;
		}
		else if (deltaX < PI)
		{
			moveX = (0.01f - (deltaX - 1.57f) / 157.0f) * acceleration;
			moveZ = ((1.57f - deltaX) / 157.0f) * acceleration;
		}
		else if (deltaX < PI / 2 + PI)
		{
			moveX = (PI - deltaX) / 157.0f * acceleration;
			moveZ = -(0.01f - (deltaX - PI) / 157.0f) * acceleration;
		}
		else if (deltaX < PI * 2)
		{
			moveX = -(0.01f - (deltaX - (PI / 2 + PI)) / 157.0f) * acceleration;
			moveZ = -((PI / 2 + PI - deltaX) / 157.0f) * acceleration;
		}
	}
	else
	{
		if (deltaX > -(PI / 2.0f))
		{
			moveX = (deltaX / 157.0f) * acceleration;
			moveZ = (0.01f + deltaX / 157.0f) * acceleration;
		}
		else if (deltaX > -PI)
		{
			moveX = -(0.01f + (deltaX + 1.57f) / 157.0f) * acceleration;
			moveZ = ((1.57f + deltaX) / 157.0f) * acceleration;
		}
		else if (deltaX > -(PI / 2 + PI))
		{
			moveX = -((PI + deltaX) / 157.0f) * acceleration;
			moveZ = -(0.01f + (deltaX + PI) / 157.0f) * acceleration;
		}
		else if (deltaX > -(PI * 2))
		{
			moveX = (0.01f + (deltaX + (PI / 2 + PI)) / 157.0f) * acceleration;
			moveZ = -((PI / 2 + PI + deltaX) / 157.0f) * acceleration;
		}
	}

	if (keyArray[5])
	{
		moveX *= 2.0f;
		moveZ *= 2.0f;
	}

	if (keyArray[0]) cam->move(-moveX, 0.0f, -moveZ);
	else if (keyArray[1]) cam->move(moveX, 0.00f, moveZ);
	if (keyArray[2]) cam->move(-moveZ, 0.0f, moveX);
	else if (keyArray[3]) cam->move(moveZ, 0.0f, -moveX);
	if (keyArray[4]) cam->move(0.0f, -SPEED_CAMERA, 0.0f);
	else if (keyArray[6]) cam->move(0.0f, SPEED_CAMERA, 0.0f);

	/*glm::vec3 p;
	cam->getPos(p.x, p.y, p.z);
	this->pos = p;*/
}

glm::vec3 Player::getPos() const
{
	return this->pos;
}