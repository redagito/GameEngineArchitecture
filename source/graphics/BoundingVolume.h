#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "core/Object.h"
#include "math/Transformation.h"

class BoundingVolume : public Object
{
   public:
    BoundingVolume();
    virtual ~BoundingVolume();

    virtual void setCenter(const glm::vec3& center) = 0;
    virtual const glm::vec3& getCenter() const = 0;

    virtual void setRadius(float radius) = 0;
    virtual float getRadius() const = 0;

    virtual void computeFromData(const std::vector<glm::vec3>& vertices) = 0;

    /**
     * Transforms bounding volume and stores in result
     * TODO Use reference for out parameter
     */
    virtual void transformBy(const Transformation& transform, BoundingVolume* result) = 0;

    virtual int whichSide(const Plane3& plane) const = 0;

    virtual bool testIntersection(const glm::vec3& origin, const glm::vec3& direction) const = 0;

    virtual bool testIntersection(const BoundingVolume* in) const = 0;

    virtual void copyFrom(const BoundingVolume* in) = 0;

    virtual void growToContain(const BoundingVolume* in) = 0;

    virtual bool contains(const glm::vec3& point) const = 0;

    static BoundingVolume* create();
};