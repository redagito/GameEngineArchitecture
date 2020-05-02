#include "graphics/sg/Spatial.h"

#include <cassert>

#include "graphics/sg/Light.h"

Spatial::Spatial() { m_lights = new std::set<Pointer<Light>>; }

Spatial::~Spatial() { delete m_lights; }

Spatial* Spatial::getParent() { return m_parent; }

void Spatial::setParent(Spatial* parent) { m_parent = parent; }

void Spatial::updateGeometricState(double appTime, bool initiator)
{
    updateWorldData(appTime);
    updateWorldBound();

    if (initiator)
    {
        propagateBoundToRoot();
    }
}

void Spatial::updateBoundState()
{
    updateWorldBound();
    propagateBoundToRoot();
}

void Spatial::setGlobalState(GlobalState* state)
{
    assert(state != nullptr);
    m_globalStates[state->getGlobalStateType()] = state;
}

GlobalState* Spatial::getGlobalState(GlobalState::Type type)
{
    auto iter = m_globalStates.find(type);
    if (iter == m_globalStates.end())
        return nullptr;
    return iter->second;
}

void Spatial::removeGlobalState(GlobalState::Type type) { m_globalStates.erase(type); }

void Spatial::removeAllGlobalStates() { m_globalStates.clear(); }

void Spatial::setLight(Light* light) { m_lights->insert(light); }

size_t Spatial::getLightQuantity() const { return m_lights->size(); }

Light* Spatial::getLight(size_t index)
{
    size_t i = 0;
    for (auto light : *m_lights)
    {
        if (i == index)
            return light;
        ++i;
    }
    return nullptr;
}

void Spatial::removeLight(Light* light) { m_lights->erase(light); }

void Spatial::removeAllLights() { m_lights->clear(); }

void Spatial::setEffect(Effect* effect) { m_effect = effect; }

Effect* Spatial::getEffect() { return m_effect; }

void Spatial::updateRenderState()
{
    GlobalStateArrayStack globalStates;
    std::stack<Light*> lights;

    // Stack initialized with default global states
    for (size_t i = 0; i < globalStates.size(); ++i)
    {
        globalStates[i].push(GlobalState::default[ i ]);
    }

    // Initially no lights
    assert(lights.empty());

    // Traverse to root and push states from root to this node
    propagateStateFromRoot(globalStates, lights);

    // Propagate new states to subtree
    updateState(globalStates, lights);
}

void Spatial::updateRenderState(GlobalStateArrayStack& globalStates, std::stack<Light*>& lights)
{
    // Push states at this node
    pushState(globalStates, lights);

    // Propagate new states to subtree
    updateState(globalStates, lights);

    // Pop states at this node
    popState(globalStates, lights);
}

void Spatial::updateWorldData(double appTime)
{
    updateControllers(appTime);

    // TODO Update controllers for global state and lights at this spoint

    if (worldIsCurrent)
        return;

    if (m_parent != nullptr)
        world.product(m_parent->world, local);
    else
        world = local;
}

void Spatial::propagateBoundToRoot()
{
    if (m_parent == nullptr)
        return;

    m_parent->updateWorldBound();
    m_parent->propagateBoundToRoot();
}