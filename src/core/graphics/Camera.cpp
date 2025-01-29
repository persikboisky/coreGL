#include "Camera.h"
#include "../window/Window.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Camera::Camera(float posX, float posY, float posZ, float fov)
{
	this->pos = glm::vec3(posX, posY, posZ);
	this->fov = glm::radians(fov);

	this->x = glm::vec3(rot * glm::vec4(1, 0, 0, 1));
	this->y = glm::vec3(rot * glm::vec4(0, 1, 0, 1));
	this->z = glm::vec3(rot * glm::vec4(0, 0, -1, 1));
}

void Camera::rotate(float x, float y, float z)
{
	this->rot = glm::rotate(this->rot, x, glm::vec3(1, 0, 0));
	this->rot = glm::rotate(this->rot, y, glm::vec3(0, 1, 0));
	this->rot = glm::rotate(this->rot, z, glm::vec3(0, 0, 1));

	this->x = glm::vec3(this->rot * glm::vec4(1, 0, 0, 1));
	this->y = glm::vec3(this->rot * glm::vec4(0, 1, 0, 1));
	this->z = glm::vec3(this->rot * glm::vec4(0, 0, -1, 1));
}

void Camera::resetRotate()
{
	Camera::rot = glm::mat4(1.0f);
}

void Camera::move(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
}

glm::mat4 Camera::getProj(int width, int height)
{
	float aspect = float(width / height);
	return glm::perspective(this->fov, aspect, 0.01f, 100.0f);
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(this->pos, this->pos + this->z, this->y);
}