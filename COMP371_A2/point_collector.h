#pragma once

#include "glew.h"
#include <vector>
#include "glm.hpp"
#include "glfw3.h"
#include "flatten.h"
#include "hermitespline.h"

class PointCollector
{
	const int m_numPoints;
	std::vector<glm::vec3> m_points;
	std::vector<GLfloat> m_pointCoordinates;
	std::vector<GLfloat> m_tangentCoordinates;
	std::vector<GLuint> m_indices;

	GLuint pointsVAO;
	GLuint pointsVBO;

	GLuint tangentVAO;
	GLuint tangentVBO;
	GLuint tangentEBO;

	void addPoint(const glm::vec3 point);
	void addTangent(const glm::vec3 tangent);
	void updatePointsVBO();
	void updateTangentVBO();

public:

	// Constructors
	PointCollector(const int numPoints);

	// Collect points and tangents
	void collectPoint(const glm::vec3 point);

	// Checks if the point collector has collected all required points
	bool isFull() const;

	void draw() const;

	HermiteSpline hermiteSpline() const;
};