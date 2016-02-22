#pragma once

#include "glm.hpp"

// Origin
const glm::vec3 origin(0.0f, 0.0f, 0.0f);


// Directions in plane
const glm::vec3 up		( 0.0f,  1.0f,  0.0f);
const glm::vec3 down	( 0.0f, -1.0f,  0.0f);

const glm::vec3 left	(-1.0f,  0.0f,  0.0f);
const glm::vec3 right	( 1.0f,  0.0f,  0.0f);

const glm::vec3 forward	( 0.0f,  0.0f,  1.0f);
const glm::vec3 backward( 0.0f,  0.0f, -1.0f);