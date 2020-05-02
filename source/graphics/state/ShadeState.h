#pragma once

#include "graphics/state/GlobalState.h"

class ShadeState : public GlobalState
{
   public:
    ShadeState() = default;
    virtual ~ShadeState() = default;

    virtual Type getGlobalStateType() const override;

    enum class Shading
    {
        // Flat shading
        Flat,
        // Smooth shading, Gouraud
        Smooth,

        Max
    };

    Shading shade = Shading::Smooth;
};