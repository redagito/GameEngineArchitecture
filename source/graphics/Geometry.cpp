#include "graphics/Geometry.h"

Geometry::Geometry(const std::vector<glm::vec3>& vertices) : vertices(vertices) {}

Geometry::Geometry(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices)
    : vertices(vertices), indices(indices)
{
}

void Geometry::updateModelState(bool updateNormals) {}

void Geometry::updateModelBound() {}

void Geometry::updateModelNormals() {}

void Geometry::updateWorldBound()
{
    // Transform model bound with world transformation
    // and store in world bound
    modelBound->transformBy(world, worldBound);
}