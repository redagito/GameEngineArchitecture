#pragma once

#include <stack>

#include "graphics/sg/Spatial.h"

class Renderer;

class Light : public Spatial
{
   public:
    enum class Type
    {
        Ambient,
        Directional,
        Point,
        Spot,

        Max
    };

    Light(Type type = Type::Ambient);
    virtual ~Light();

    Type type = Type::Ambient;
    glm::vec4 ambient = glm::vec4{0.f, 0.f, 0.f, 1.f};
    glm::vec4 diffuse = glm::vec4{0.f, 0.f, 0.f, 1.f};
    glm::vec4 specular = glm::vec4{0.f, 0.f, 0.f, 1.f};

    // Attunuation calculation
    // a = 1 / (C + L * d + Q * d ^ 2)
    // a = attunuation factor
    // C = constant
    // L = linear
    // Q = quadratic
    // d = distance
    float intensity = 1.f;
    float constant = 1.f;
    float linear = 0.f;
    float quadratic = 0.f;

    bool attenuate = false;
    bool on = true;

    // Spot light parameters, only for Type::Spot
    float exponent = 1.f;
    float angle = 0.f;

    // Light frame, local coordinates
    void setFrame(const glm::vec3& location = glm::vec3{0.f}, const glm::vec3& direction = glm::vec3{0.f, 0.f, -1.f},
                  const glm::vec3& up = glm::vec3{0.f, 1.f, 0.f}, const glm::vec3& right = glm::vec3{1.f, 0.f, 0.f});

    void setFrame(const glm::vec3& location, const glm::mat3& axes);

    void setLocation(const glm::vec3& location);
    void setAxes(const glm::vec3& direction, const glm::vec3& up, const glm::vec3& right);
    void setAxes(const glm::mat3& axes);

    // local.translate
    const glm::vec3& getLocation() const;
    // local.rotate, column 0
    const glm::vec3& getDirection() const;
    // local.rotate, column 1
    const glm::vec3& getUp() const;
    // local.rotate, column 2
    const glm::vec3& getRight() const;

    // For directional lights, the direction vector must be unit length
    // Up and right vector are generated automatically
    void setDirection(const glm::vec3& direction);

    // Light frame, world coordinates
    // world.translate
    const glm::vec3& getWorldLocation() const;
    // world.rotate, column 0
    const glm::vec3& getWorldDirection() const;
    // world.rotate, column 1
    const glm::vec3& getWorldUp() const;
    // world.rotate, column 2
    const glm::vec3& getWorldRight() const;

   private:
    // Updates
    virtual void updateWorldBound() override;
    void onFrameChange();

    // base class functions not supported
    virtual void udpateState(const std::stack<GlobalState*>& states, const std::stack<Light*>& lights);
    virtual void draw(Renderer& renderer, bool);
};