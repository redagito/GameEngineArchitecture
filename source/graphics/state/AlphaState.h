#pragma once

#include "graphics/state/GlobalState.h"

class AlphaState : public GlobalState
{
   public:
    AlphaState() = default;
    virtual ~AlphaState() = default;

    virtual Type getGlobalStateType() const override;

    // Source blend modes
    enum class SrcBlend
    {
        Zero,
        One,
        DstColor,
        OneMinusDstColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        SrcAlphaSaturate,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha,

        // Keep at end
        Max
    };

    // Destination blend modes
    enum class DstBlend
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha,

        // Keep at end
        Max
    };

    // Alpha test mode
    enum class Test
    {
        Never,         // false
        Always,        // true
        Equal,         // ==
        NotEqual,      // !=
        Less,          // <
        LessEqual,     // <=
        Greater,       // >
        GreaterEqual,  // >=

        // Keep at end
        Max
    };

    bool blendEnabled = false;
    SrcBlend srcBlend = SrcBlend::SrcAlpha;
    DstBlend dstBlend = DstBlend::OneMinusSrcAlpha;

    bool testEnabled = false;
    Test test = Test::Always;
    // Range [0-1]
    float reference = 0.f;
};