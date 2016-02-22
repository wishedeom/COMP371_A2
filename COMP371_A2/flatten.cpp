#include "stdafx.h"
#include "flatten.h"

// Takes a std::vector of glm::vec3 and returns an std::vector of the individual components, in (x, y, z) order.
std::vector<GLfloat> flatten(const std::vector<glm::vec3> vertices)
{
	std::vector<GLfloat> coordinates;
	for (auto vertex : vertices)
	{
		coordinates.push_back(vertex.x);
		coordinates.push_back(vertex.y);
		coordinates.push_back(vertex.z);
	}
	return coordinates;
}