#include "Camera.h"
#include "../window/window.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

glm::vec3 Camera::x;
glm::vec3 Camera::y;
glm::vec3 Camera::z;
glm::vec3 Camera::pos;
glm::mat4 Camera::rot(1.0f);

float Camera::fov;

Camera::Camera(float posX, float posY, float posZ, float fov)
{
	Camera::pos = glm::vec3(posX, posY, posZ);
	Camera::fov = glm::radians(fov);

	x = glm::vec3(rot * glm::vec4(1, 0, 0, 1));
	y = glm::vec3(rot * glm::vec4(0, 1, 0, 1));
	z = glm::vec3(rot * glm::vec4(0, 0, -1, 1));
}

void Camera::rotate(float x, float y, float z)
{
	Camera::rot = glm::rotate(Camera::rot, x, glm::vec3(1, 0, 0));
	Camera::rot = glm::rotate(Camera::rot, y, glm::vec3(0, 1, 0));
	Camera::rot = glm::rotate(Camera::rot, z, glm::vec3(0, 0, 1));

	Camera::x = glm::vec3(rot * glm::vec4(1, 0, 0, 1));
	Camera::y = glm::vec3(rot * glm::vec4(0, 1, 0, 1));
	Camera::z = glm::vec3(rot * glm::vec4(0, 0, -1, 1));
}

void Camera::resetRotate()
{
	Camera::rot = glm::mat4(1.0f);
}

void Camera::move(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

glm::mat4 Camera::getProj()
{
	float aspect = float(window::width) / float(window::height);
	return glm::perspective(fov, aspect, 0.01f, 100.0f);
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(Camera::pos, Camera::pos + Camera::z, Camera::y);
}