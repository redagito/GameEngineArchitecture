#pragma once

#include "graphics/Geometry.h"

/**
 * Triangle mesh
 */
class TriMesh : public Geometry
{
   public:
    TriMesh(const std::vector<glm::vec3>& vertices, const std::vector<std::uint32_t>& indices, bool generateNormals,
            bool cacheNormals);
    virtual ~TriMesh() = default;

    size_t getTriangleQuantity() const;
    void generateNormals();

   protected:
    TriMesh();
    virtual void updateModelNormals();
};