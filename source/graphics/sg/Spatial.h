#pragma once

#include <array>
#include <set>
#include <stack>
#include <unordered_map>

#include "core/Object.h"
#include "graphics/BoundingVolume.h"
#include "graphics/Effect.h"
#include "graphics/state/GlobalState.h"
#include "math/Transformation.h"

class Light;

/**
 * Represents a coordinate system in space
 */
class Spatial : public Object
{
   public:
    Spatial();
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

    /**
     * Light support
     */
    void setLight(Light* light);
    size_t getLightQuantity() const;
    Light* getLight(size_t index);
    void removeLight(Light* light);
    void removeAllLights();

    /**
     * Effect support
     */
    virtual void setEffect(Effect* effect);
    Effect* getEffect();

    /**
     * Render state support
     */
    using GlobalStateArrayStack = std::array<std::stack<GlobalState*>, static_cast<size_t>(GlobalState::Type::Max)>;

    // Initialtor
    virtual void updateRenderState();
    virtual void updateRenderState(GlobalStateArrayStack& globalStates, std::stack<Light*>& lights);

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

    void propagateStateFromRoot(GlobalStateArrayStack& globalStates, std::stack<Light*>& lights);
    void pushState(GlobalStateArrayStack& globalStates, std::stack<Light*>& lights);
    void popState(GlobalStateArrayStack& globalStates, std::stack<Light*>& lights);

    /**
     * Stacks assemble the states and lights during depth first traversal
     */
    virtual void updateState(GlobalStateArrayStack& globalStates, std::stack<Light*>& lights) = 0;

   protected:
    std::set<Pointer<Light>>* m_lights = nullptr;
    Pointer<Effect> m_effect;

   private:
    Spatial* m_parent = nullptr;
};