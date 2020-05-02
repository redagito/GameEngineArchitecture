#pragma once

#include "graphics/state/GlobalState.h"

class ZBufferState : public GlobalState
{
   public:
    virtual Type getGlobalStateType() const override;

    ZBufferState() = default;
    virtual ~ZBufferState() = default;

    // Comparison function
    enum class Compare
    {
        Never,         // false
        Always,        // true
        Equal,         // ==
        NotEqual,      // !=
        Less,          // <
        LessEqual,     // <=
        Greater,       // >
        GreaterEqual,  // >=

        Max
    };

    bool enabled = true;
    bool writable = true;
    Compare compare = Compare::LessEqual;
};