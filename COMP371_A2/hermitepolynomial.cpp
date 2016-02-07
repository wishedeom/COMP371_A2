#include "stdafx.h"
#include "hermitepolynomial.h"

// Constructs a hermite polynomial from two interpolation points and their tangents
HermitePolynomial::HermitePolynomial(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 t1, const glm::vec3 t2)
{
	m_a = 2.0f * p1 - 2.0f * p2 + t1 + t2;
	m_b = -3.0f * p1 + 3.0f * p2 - 2.0f * t1 - t2;
	m_c = t1;
	m_d = p1;
}

// Accessors
auto HermitePolynomial::a() const { return m_a; }
auto HermitePolynomial::b() const { return m_b; }
auto HermitePolynomial::c() const { return m_c; }
auto HermitePolynomial::d() const { return m_d; }

// Evaluates the polynomial function with the given parameter
glm::vec3 HermitePolynomial::evaluate(const GLfloat u) const
{
	return u * u * u * m_a + u * u * m_b + u * m_c + m_d;
}