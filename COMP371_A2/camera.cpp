#include "stdafx.h"
#include "camera.h"

Camera::Camera()
{
	m_position = glm::vec3(0.0f, 0.0f, 1.0f);
	m_orientation = c_forward;
	m_up = c_up;
}

Camera::Camera(const glm::vec3 position, const glm::vec3 orientation, const glm::vec3 up)
{
	m_position = position;
	m_orientation = orientation;
	m_up = up;
}

// Accessors
auto Camera::position() const { return m_position; }
auto Camera::orientation() const { return m_orientation; }
auto Camera::up() const { return m_up; }

// Mutators
void Camera::setPosition(const glm::vec3 position) { m_position = position; }
void Camera::setOrientation(const glm::vec3 orientation) { m_orientation = orientation; }
void Camera::setUp(const glm::vec3 up) { m_up = up; }