#pragma once

#include "graphics/state/GlobalState.h"

class WireframeState : public GlobalState
{
   public:
    WireframeState() = default;
    virtual ~WireframeState() = default;

    virtual Type getGlobalStateType() const override;

    bool enabled = false;
};