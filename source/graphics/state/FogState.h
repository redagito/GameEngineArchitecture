#pragma once

#include <glm/glm.hpp>

#include "graphics/state/GlobalState.h"

class FogState : public GlobalState
{
   public:
    FogState() = default;
    virtual ~FogState() = default;

    virtual Type getGlobalStateType() const override;

    // Fog density function
    enum class Density
    {
        Linear,
        Exp,
        ExpSqr,

        Max
    };

    enum class Apply
    {
        PerVertex,
        PerPixel,

        Max
    };

    bool enabled = false;
    float start = 0.f;
    float end = 1.f;
    float density = 1.f;
    glm::vec4 color = glm::vec4{0.f, 0.f, 0.f, 1.f};
    Density densityFunc = Density::Linear;
    Apply apply = Apply::PerVertex;
};
