#pragma once

class Renderer
{
   public:
    using DrawFunction = void (*)();

    void drawPrimitive();
    void drawEnvironmentMap();
};