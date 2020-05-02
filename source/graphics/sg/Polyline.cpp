#include "graphics/sg/Polyline.h"

Polyline::Polyline(const std::vector<glm::vec3>& vertices, bool closed, bool contiguous)
    : m_closed(closed), m_contiguous(contiguous)
{
    setGeometryType();
}

void Polyline::setActiveQuantity(size_t activeQuantity) { m_activeQuantity = activeQuantity; }

size_t Polyline::getActiveQuantity() const { return m_activeQuantity; }

void Polyline::setClosed(bool closed) { m_closed = closed; }

bool Polyline::getClosed() const { return m_closed; }

void Polyline::setContiguous(bool contiguous) { m_contiguous = contiguous; }

bool Polyline::getContiguous() const { return m_contiguous; }

Polyline::Polyline() { setGeometryType(); }

void Polyline::setGeometryType()
{
    if (m_contiguous)
    {
        if (m_closed)
        {
            geometryType = GeometryType::PolylineClosed;
        }
        else
        {
            geometryType = GeometryType::PolylineOpen;
        }
    }
    else
    {
        geometryType = GeometryType::PolylineSegments;
    }
}