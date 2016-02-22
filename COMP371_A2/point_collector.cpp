#include "stdafx.h"
#include "glew.h"
#include "point_collector.h"
#include <iostream>
#include "vec3_to_string.h"

// Constructors
PointCollector::PointCollector(const int numPoints)
	: m_numPoints(numPoints)
	, m_points(0)
{
	m_points.reserve(m_numPoints);

	glGenVertexArrays(1, &pointsVAO);
	glGenBuffers(1, &pointsVBO);

	glGenVertexArrays(1, &tangentVAO);
	glGenBuffers(1, &tangentVBO);
	glGenBuffers(1, &tangentEBO);
}


// Adds points, then tangents, until both are full. Returns true if and only if there is still room for points or tangents.
void PointCollector::collectPoint(const glm::vec3 point)
{
	if (m_points.size() < m_numPoints)
	{
		addPoint(point);
	}
	else if (m_points.size() < 2 * m_numPoints)
	{
		addTangent(point);
	}
}


void PointCollector::addPoint(const glm::vec3 point)
{
	m_points.push_back(point);
	updatePointsVBO();
}

void PointCollector::addTangent(const glm::vec3 point)
{
	m_points.push_back(point);
	updatePointsVBO();
	updateTangentVBO();
}


void PointCollector::updatePointsVBO()
{
	m_pointCoordinates = flatten(m_points);

	glBindVertexArray(pointsVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_pointCoordinates[0]) * m_pointCoordinates.size(), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_pointCoordinates[0]) * m_pointCoordinates.size(), &m_pointCoordinates[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}


void PointCollector::updateTangentVBO()
{
	for (int i = 0; i < m_points.size() - m_numPoints; i++)
	{
		m_indices.push_back(i);
		m_indices.push_back(i + m_numPoints);
	}
	m_tangentCoordinates = flatten(m_points);

	glBindVertexArray(tangentVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof m_tangentCoordinates[0] * m_tangentCoordinates.size(), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof m_tangentCoordinates[0] * m_tangentCoordinates.size(), &m_tangentCoordinates[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tangentEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof m_indices[0] * m_indices.size(), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof m_indices[0] * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}


bool PointCollector::isFull() const
{
	return m_points.size() >= 2 * m_numPoints;
}


void PointCollector::draw() const
{
	glBindVertexArray(pointsVAO);
	glDrawArrays(GL_POINTS, 0, m_points.size());
	glBindVertexArray(tangentVAO);
	glDrawElements(GL_LINES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}


HermiteSpline PointCollector::hermiteSpline() const
{
	std::vector<glm::vec3> points;
	std::vector<glm::vec3> tangents;
	const int actualNumPoints = m_points.size() - m_numPoints;
	for (int i = 0; i < actualNumPoints; i++)
	{
		points.push_back(m_points[i]);
		tangents.push_back(m_points[i + m_numPoints]);
	}
	return HermiteSpline(points, tangents);
}