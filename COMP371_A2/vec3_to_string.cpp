#include "stdafx.h"
#include "vec3_to_string.h"

std::string vec3ToString(const glm::vec3 v)
{
	return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
}