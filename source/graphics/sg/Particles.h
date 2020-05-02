#pragma once

#include "graphics/sg/TriMesh.h"

class Camera;

/**
 * A particle is a geometric primitive with location and size
 * Represents a collection of particles, also called a particle system
 */
class Particles : public TriMesh
{
   public:
    Particles(const std::vector<glm::vec3>& locations, const std::vector<float>& sizes, bool wantNormals);

    virtual ~Particles() = default;

    std::vector<glm::vec3> locations;
    std::vector<float> sizes;
    // For uniform scale, multiplied by sizes
    float sizeAdjust = 1.f;

    void setActiveQuantity(size_t activeQuantity);
    size_t getActiveQuantity() const;

   protected:
    Particles();
    void generateParticles(const Camera* camera);

    size_t m_activeQuantity = 0;
};