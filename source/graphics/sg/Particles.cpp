#include "graphics/sg/Particles.h"

Particles::Particles(const std::vector<glm::vec3>& locations, const std::vector<float>& sizes, bool wantNormals)
    : locations(locations), sizes(sizes)
{
}

void Particles::setActiveQuantity(size_t activeQuantity) {}

size_t Particles::getActiveQuantity() const { return m_activeQuantity; }

Particles::Particles() {}
void Particles::generateParticles(const Camera* camera) {}