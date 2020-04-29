#pragma once

#include "core/Object.h"
#include "graphics/BoundingVolume.h"
#include "math/Transformation.h"

/**
 * Represents a coordinate system in space
 */
class Spatial : public Object
{
   public:
    virtual ~Spatial();

    Spatial* getParent();

    // Internal use only
    void setParent(Spatial* parent);

    /**
     * For geometric updates
     */
    Transformation local;
    Transformation world;

    bool worldIsCurrent = false;
    bool worldBoundIsCurrent = false;

    Pointer<BoundingVolume> worldBound;

    // TODO Time delta or actual time since app started?
    void updateGeometricState(double appTime, bool initiator = true);
    void updateBoundState();

   protected:
    virtual void updateWorldData(double appTime);
    virtual void updateWorldBound() = 0;

    // Calculate world bounding volumes in upward pass
    void propagateBoundToRoot();

   private:
    Spatial* m_parent = nullptr;
};