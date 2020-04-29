#pragma once

#include <glm/glm.hpp>

/**
 * Parameterized plane
 */
class Plane3
{
   public:
   private:
    // Unit length normal
    glm::vec3 normal;
    // Plane constant
    float c = 0.f;
};