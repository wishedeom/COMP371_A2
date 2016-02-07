#include "stdafx.h"
#include "hermitespline.h"

HermiteSpline::HermiteSpline(const std::vector<glm::vec3> points, const std::vector<glm::vec3> tangents)
{
	if (points.size() != tangents.size())
	{
		throw std::invalid_argument("Error constructing spline: Number of points must equal number of tangents.");
	}

	std::vector<HermitePolynomial> segments;
	for (int i = 0; i < points.size() - 1; i++)
	{
		segments.push_back(HermitePolynomial(points[i], points[i + 1], tangents[i], tangents[i + 1]));
	}
	m_segments = segments;
}

auto HermiteSpline::segments() const { return m_segments; }

Polyline HermiteSpline::polyline() const
{
	Polyline p;
	for (auto segment : m_segments)
	{
		p.pushSegment(segment);
	}
	return p;
}