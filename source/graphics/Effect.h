#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "core/Object.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"

class Effect : public Object
{
   public:
    Effect() = default;
    virtual ~Effect() = default;

    /**
     * Create clone of the effect. Color and textures are shared.
     * Derived classes cam override this behavior and decide what
     * is copied and what is shared.
     */
    virtual Effect* clone();

    // Common data used in most effects
    // Set either rgb or rgba values
    // Defaults to rgba oif both are set
    std::vector<glm::vec3> rgbs;
    std::vector<glm::vec4> rgbas;

    std::vector<Pointer<Texture>> textures;
    std::vector<glm::vec2> uvs;

    // Internal use
    // Function required to draw the effect
    Renderer::DrawFunction draw;
};