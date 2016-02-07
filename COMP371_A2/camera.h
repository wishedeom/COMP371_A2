#pragma once

#include "glm.hpp" // Vector types

const glm::vec3 c_origin(0.0f, 0.0f, 0.0f);
const glm::vec3 c_up(0.0f, 1.0f, 0.0f);
const glm::vec3 c_forward(0.0f, 0.0f, -1.0f);

class Camera
{

	glm::vec3 m_position;		// Location of the camera's eye
	glm::vec3 m_orientation;	// Direction the camera's eye is pointing
	glm::vec3 m_up;				// The camera's local up vector

public:

	// Constructors
	Camera();
	Camera(const glm::vec3 position, const glm::vec3 orientation, const glm::vec3 up);

	// Accessors
	auto position() const;
	auto orientation() const;
	auto up() const;

	// Mutators
	void setPosition(const glm::vec3 position);
	void setOrientation(const glm::vec3 orientation);
	void setUp(const glm::vec3 up);

};