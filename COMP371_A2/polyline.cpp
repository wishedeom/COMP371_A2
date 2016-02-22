#include "stdafx.h"
#include "glew.h"
#include "polyline.h"
#include "flatten.h"


Polyline::Polyline()
	:	lines(true)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

// Accessor
std::vector<glm::vec3> Polyline::points() const { return m_points; }

std::vector<GLuint> Polyline::indices() const
{
	std::vector<GLuint> indexVector;
	for (int i = 0; i < m_points.size(); i++)
	{
		indexVector.push_back(i);
	}
	return indexVector;
}

// Adds a polyline approximation of a single Hermite polynomial segment to the polyline
void Polyline::pushSegment(const HermitePolynomial& p)
{
	const GLfloat uStep = 0.0001f;
	for (GLfloat u = 0.0f; u <= 1.0f; u += uStep)
	{
		m_points.push_back(p.evaluate(u));
	}

	auto coordinates = flatten(points());
	m_indices = indices();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof coordinates[0] * coordinates.size(), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof coordinates[0] * coordinates.size(), &coordinates[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof m_indices[0]  * m_indices.size(), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof m_indices[0]  * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}


void Polyline::setLines()
{
	lines = true;
}


void Polyline::setPoints()
{
	lines = false;
}


void Polyline::draw() const
{
	glBindVertexArray(VAO);
	if (lines)
	{
		glDrawElements(GL_LINE_STRIP, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	}
	else
	{
		glDrawArrays(GL_POINTS, 0, m_points.size());
	}
	glBindVertexArray(0);
}