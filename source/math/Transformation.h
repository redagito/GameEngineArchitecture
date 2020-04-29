#pragma once

#include <glm/glm.hpp>

#include "math/Plane3.h"

class Transformation
{
   public:
    Transformation();
    ~Transformation();

    static const Transformation IDENTITY;

    void setRotate(const glm::mat3& rotate);
    const glm::mat3& getRotate() const;

    void setMatrix(const glm::mat3& matrix);
    const glm::mat3& getMatrix() const;

    void setTranslate(const glm::vec3& translate);
    const glm::vec3& getTranslate() const;

    void setScale(const glm::vec3& scale);
    const glm::vec3& getScale() const;

    void setUniformScale(const float scale);
    float getUniformScale() const;

    float getNorm() const;

    void makeIdentity();
    void makeUnitScale();

    bool isIdentity() const;
    bool isRSMatrix() const;
    bool isUniformScale() const;

    glm::vec3 applyForward(const glm::vec3& in);
    void applyForward(size_t count, const glm::vec3* in, glm::vec3* out);

    Plane3 applyForward(const Plane3& in) const;

    glm::vec3 applyInverse(const glm::vec3& in);
    void applyInverse(size_t count, const glm::vec3* in, glm::vec3* out);

    void product(const Transformation& a, const Transformation& b);
    void inverse(const Transformation& inverse);

    glm::vec3 invertVector(const glm::vec3& in);

   private:
    // Rotation or general transformation
    glm::mat3 m_matrix = glm::mat3{0.f};
    glm::vec3 m_translate = glm::vec3{0.f};
    glm::vec3 m_scale = glm::vec3{1.f};

    bool m_isIdentity = false;
    bool m_isRSMatrix = false;
    bool m_isUniformScale = false;
};