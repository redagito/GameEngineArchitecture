#pragma once

#include <type_traits>

#include "core/Object.h"

/**
 * The global render state
 */
class GlobalState : public Object
{
   public:
    virtual ~GlobalState() = default;

    enum class Type
    {
        Alpha,
        Cull,
        Dither,
        Fog,
        Material,
        Shade,
        Wireframe,
        ZBuffer,

        // Keep at end
        Max
    };

    virtual Type getGlobalStateType() const = 0;

    static Pointer<GlobalState> default[ static_cast<std::underlying_type<Type>::type>(Type::Max) ];

   protected:
    GlobalState() = default;
};