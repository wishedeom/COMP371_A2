#pragma once
#include <vector>
#include "glfw3.h"
#include "glm.hpp"

// Flattens an std::vector of n glm::vec3s into an std::vector of 3 * n GLfloats.
std::vector<GLfloat> flatten(const std::vector<glm::vec3> vertices);