#include "graphics/sg/Node.h"

Node::Node(size_t quantity) { m_children.resize(quantity); }

Node::~Node() {}

size_t Node::getQuantity() const { return m_children.size(); }

size_t Node::getUsed() const { return m_used; }

size_t Node::attachChild(Spatial* child)
{
    if (child == nullptr)
        return 0;
    // Attach child
    ++m_used;

    // Search for empty spot
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (m_children.at(i) == nullptr)
        {
            m_children.at(i) = Pointer<Spatial>{child};
            return i;
        }
    }

    // Append
    m_children.push_back(Pointer<Spatial>{child});
    return m_children.size() - 1;
}

size_t Node::detachChild(const Spatial* child)
{
    if (child == nullptr)
        return 0;

    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (m_children.at(i) == child)
        {
            m_children.at(i) = nullptr;
            --m_used;
            return i;
        }
    }
    // TODO What to do when not found?
    return 0;
}

Pointer<Spatial> Node::detachChildAt(size_t index)
{
    auto ptr = m_children.at(index);

    if (ptr != nullptr)
    {
        // Detach child
        m_children.at(index) = nullptr;
        --m_used;
    }
    return ptr;
}

Pointer<Spatial> Node::setChild(size_t index, Spatial* child)
{
    // Spot empty
    if (m_children.at(index) == nullptr && child != nullptr)
        ++m_used;
    else if (m_children.at(index) != nullptr && child == nullptr)
        --m_used;

    m_children.at(index) = Pointer<Spatial>{child};
    return m_children.at(index);
}

Pointer<Spatial> Node::getChild(size_t index) { return m_children.at(index); }

void Node::updateWorldData(double appTime)
{
    Spatial::updateWorldData(appTime);
    for (auto& child : m_children)
    {
        if (child != nullptr)
            child->updateGeometricState(appTime, false);
    }
}

void Node::updateWorldBound()
{
    if (worldBoundIsCurrent)
        return;

    bool foundFirstBound = false;
    for (auto child : m_children)
    {
        if (child == nullptr)
            continue;
        if (foundFirstBound)
        {
            // Merge current world bound with child bound
            worldBound->growToContain(child->worldBound);
        }
        else
        {
            // Set world bound to bound of first valid child
            foundFirstBound = true;
            worldBound->copyFrom(child->worldBound);
        }
    }
}