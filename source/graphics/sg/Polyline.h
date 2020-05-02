#pragma once

#include "graphics/sg/Geometry.h"

class Polyline : public Geometry
{
   public:
    Polyline(const std::vector<glm::vec3>& vertices, bool closed, bool contiguous);
    virtual ~Polyline() = default;

    void setActiveQuantity(size_t activeQuantity);
    size_t getActiveQuantity() const;

    void setClosed(bool closed);
    bool getClosed() const;

    void setContiguous(bool contiguous);
    bool getContiguous() const;

   protected:
    Polyline();
    void setGeometryType();

    size_t m_activeQuantity = 0;
    bool m_closed = false;
    bool m_contiguous = false;
};