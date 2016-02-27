#pragma once
#include "glm.hpp"
#include <string>

// Takes a glm::vec3 and returns a string representation of the 3-tuple of its components.
// If a vector has components x, y, and z, returns "(x, y, z)".
std::string vec3ToString(const glm::vec3 v);