#pragma once

#include <glm/glm.hpp>

#include "graphics/state/GlobalState.h"

class CullState : public GlobalState
{
   public:
    CullState() = default;
    virtual ~CullState() = default;

    virtual Type getGlobalStateType() const override;

    // Order of front faces
    enum class Order
    {
        // Counterclockwise
        CCW,
        // Clockwise
        CW,

        Max
    };

    // Which faces to cull
    enum class Cull
    {
        // Front facing
        Front,
        // Back facing
        Back,

        Max
    };

    bool enabled = true;
    Order frontFace = Order::CCW;
    Cull cullFace = Cull::Back;
};