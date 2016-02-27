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


// Evaluates the first derivative at a given parameter value
glm::vec3 HermitePolynomial::evaluateDerivative(const GLfloat u) const
{
	return 3 * u * u * m_a + 2 * u * m_b + m_c;
}


// Evaluates the second derivative at a given parameter value
glm::vec3 HermitePolynomial::evaluateSecondDerivative(const GLfloat u) const
{
	return 6.f * u * m_a + 2.f * m_b;
}


// Evaluates the first derivative of the unit tangent vector at a given parameter value
glm::vec3 HermitePolynomial::evaluateDerivativeOfUnitTangent(const GLfloat u) const
{
	const auto dg = evaluateDerivative(u);						// First derivative
	const auto ddg = evaluateSecondDerivative(u);				// Second derivative
	const auto ndg = glm::length(dg);							// Norm of first derivative
	const auto dndg = evaluateDerivativeOfNormedDerivative(u);	// Derivative of norm of first derivative
	return 1.f / (ndg * ndg) * (ndg * ddg - dndg * dg);
}


// Evaluates the first derivative of the norm of the first derivatve at a given parameter value
GLfloat HermitePolynomial::evaluateDerivativeOfNormedDerivative(const GLfloat u) const
{
	return 36.f * glm::length(m_a) * glm::length(m_a) * u * u * u
		+ 36.f * glm::dot(m_a, m_b) * u * u
			+ (8.f * glm::length(m_b) * glm::length(m_b)
				+ 12.f * glm::dot(m_a, m_c)) * u
					+ 2.f * glm::dot(m_b, m_c);
}


// Evaluates the curvature at a given parameter value
GLfloat HermitePolynomial::evaluateCurvature(const GLfloat u) const
{
	return 1.f / glm::length(evaluateDerivative(u)) * glm::length(evaluateDerivativeOfUnitTangent(u));
}