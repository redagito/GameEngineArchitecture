#include "graphics/Spatial.h"

#include <cassert>

Spatial::~Spatial() {}

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