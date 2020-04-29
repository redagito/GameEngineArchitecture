#include "graphics/Spatial.h"

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

void Spatial::updateBoundState() {}

void Spatial::updateWorldData(double appTime)
{
    updateControllers(appTime);

    // TODO Update controllers for global state and lights

    if (worldIsCurrent)
        return;

    if (m_parent != nullptr)
        world.product(m_parent->world, local);
    else
        world = local;
}

void Spatial::propagateBoundToRoot() {}