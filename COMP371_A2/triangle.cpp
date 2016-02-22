#include "stdafx.h"
#include "glew.h"
#include "triangle.h"
#include "gtc/matrix_transform.hpp"
#include <iostream>
#include "vector_constants.h"
#include <string>
#include "vec3_to_string.h"

const float pi = 3.1415926535897932385f;

Triangle::Triangle(const GLfloat length, const GLfloat width, const glm::vec3 centre, const glm::vec3 orientation)
	:	m_length(length)
	,	m_width(width)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	set(centre, orientation);
}


void Triangle::set(const glm::vec3 centre, const glm::vec3 orientation)
{
	m_centre = centre;
	m_orientation = orientation;

	lowerLeft = glm::vec4(-m_width / 2, -m_length / 2, 0.0f, 1.f);
	lowerRight = glm::vec4(m_width / 2, -m_length / 2, 0.0f, 1.f);
	top = glm::vec4(0.0f, m_length / 2, 0.f, 1.f);

	const GLfloat rotAngle = angle(up, orientation);

	// rotate, translate back to new position
	glm::mat4 transformation;
	transformation = glm::translate(transformation, glm::vec3(centre));
	transformation = glm::rotate(transformation, -rotAngle, backward);

	lowerLeft = transformation * lowerLeft;
	lowerRight = transformation * lowerRight;
	top = transformation * top;

	coordinates.clear();

	coordinates.push_back(lowerLeft.x);
	coordinates.push_back(lowerLeft.y);
	coordinates.push_back(lowerLeft.z);
	coordinates.push_back(lowerRight.x);
	coordinates.push_back(lowerRight.y);
	coordinates.push_back(lowerRight.z);
	coordinates.push_back(top.x);
	coordinates.push_back(top.y);
	coordinates.push_back(top.z);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates[0]) * coordinates.size(), nullptr, GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates[0]) * coordinates.size(), &coordinates[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}


void Triangle::orient(const glm::vec3 start, const glm::vec3 end)
{
	set(start, end - start);
}

void Triangle::snapTo(const Polyline& polyline, const int segment)
{
	const auto size = polyline.points().size();
	const auto start = polyline.points()[segment % size];
	const auto end = polyline.points()[(segment + 1) % size];
	orient(start, end);
}

void Triangle::draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

GLfloat angle(const glm::vec3 reference, const glm::vec3 orientation)
{
	const glm::vec3 nOrientation = glm::normalize(orientation);
	const glm::vec3 nReference = glm::normalize(reference);
	const GLfloat dotProduct = glm::dot(nReference, nOrientation);
	const glm::vec3 crossProduct = glm::cross(nReference, nOrientation);
	return acos(dotProduct) * signum(crossProduct.z);
}

GLfloat signum(const GLfloat x)
{
	GLfloat sign;
	if (x > 0.0f)
	{
		sign = +1.0f;
	}
	else if (x == 0.0f)
	{
		sign = 0.0f;
	}
	else
	{
		sign = -1.0f;
	}
	return sign;
}