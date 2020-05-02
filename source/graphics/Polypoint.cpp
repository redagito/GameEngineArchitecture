#include "graphics/Polypoint.h"

Polypoint::Polypoint(const std::vector<glm::vec3>& vertices) : Geometry(vertices)
{
    geometryType = GeometryType::Polypoint;
    m_activeQuantity = vertices.size();

    indices.resize(m_activeQuantity);
    for (size_t i = 0; i < m_activeQuantity; ++i)
    {
        indices[i] = i;
    }
}

void Polypoint::setActiveQuantity(size_t activeQuantity) {}

size_t Polypoint::getActiveQuantity() const { return m_activeQuantity; }

Polypoint::Polypoint() { geometryType = GeometryType::Polypoint; }