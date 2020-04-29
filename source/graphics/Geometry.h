#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "core/Pointer.h"
#include "graphics/BoundingVolume.h"

class Geometry
{
   public:
    /**
     * Geometric update for world bounds
     */
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<size_t> indices;
    Pointer<BoundingVolume> modelBound;

    void updateModelState(bool updateNormals);

   protected:
    virtual void updateModelBound();
    virtual void updateModelNormals();
    virtual void updateWorldBound();
};