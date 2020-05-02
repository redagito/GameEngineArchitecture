#pragma once

#include <unordered_map>

#include "core/Object.h"
#include "graphics/BoundingVolume.h"
#include "graphics/state/GlobalState.h"
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
    // Local transformation
    Transformation local;
    // World transformation
    Transformation world;

    bool worldIsCurrent = false;
    bool worldBoundIsCurrent = false;

    // World bound volume
    // Contains this node and all its children
    Pointer<BoundingVolume> worldBound;

    // TODO Time delta or actual time since app started?
    void updateGeometricState(double appTime, bool initiator = true);

    /**
     * Update world bounding volumes
     * Use when local transformation did not change and do not need to be propagated
     */
    void updateBoundState();

    /**
     * Global state support
     */
    void setGlobalState(GlobalState* state);
    GlobalState* getGlobalState(GlobalState::Type type);
    void removeGlobalState(GlobalState::Type type);
    void removeAllGlobalStates();

   protected:
    std::unordered_map<GlobalState::Type, Pointer<GlobalState>> m_globalStates;

    /**
     * Computes composition of the parent node world transformation
     * and the local transformation for the object
     */
    virtual void updateWorldData(double appTime);

    /**
     * Updates the world bound for this node
     */
    virtual void updateWorldBound() = 0;

    // Calculate world bounding volumes in upward pass
    void propagateBoundToRoot();

   private:
    Spatial* m_parent = nullptr;
};