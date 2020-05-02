#pragma once

#include <glm/glm.hpp>

#include "graphics/state/GlobalState.h"

class MaterialState : public GlobalState
{
   public:
    MaterialState() = default;
    virtual ~MaterialState() = default;

    virtual Type getGlobalStateType() const override;

    glm::vec4 emissive = glm::vec4{0.f, 0.f, 0.f, 1.f};
    glm::vec4 ambient = glm::vec4{0.2f, 0.2f, 0.2f, 1.f};
    glm::vec4 diffuse = glm::vec4{0.8f, 0.8f, 0.8f, 1.f};
    glm::vec4 specular = glm::vec4{0.f, 0.f, 0.f, 1.f};
    float shininess = 1.f;
};