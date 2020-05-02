#pragma once

#include "graphics/sg/Geometry.h"

class Polypoint : public Geometry
{
   public:
    Polypoint(const std::vector<glm::vec3>& vertices);
    virtual ~Polypoint() = default;

    void setActiveQuantity(size_t activeQuantity);
    size_t getActiveQuantity() const;

   protected:
    Polypoint();

    size_t m_activeQuantity = 0;
};