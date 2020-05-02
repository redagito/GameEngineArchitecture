#pragma once

#include "graphics/state/GlobalState.h"

class DitheringState : public GlobalState
{
   public:
    DitheringState() = default;
    virtual ~DitheringState() = default;

    virtual Type getGlobalStateType() const override;

    bool enabled = false;
};