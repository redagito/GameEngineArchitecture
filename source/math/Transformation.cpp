#include "math/Transformation.h"

#include <cassert>

Transformation::Transformation() {}

Transformation::~Transformation() {}

const Transformation Transformation::IDENTITY;

void Transformation::setRotate(const glm::mat3& rotate) {}

const glm::mat3& Transformation::getRotate() const { return m_matrix; }

void Transformation::setMatrix(const glm::mat3& matrix) { m_matrix = matrix; }

const glm::mat3& Transformation::getMatrix() const { return m_matrix; }

void Transformation::setTranslate(const glm::vec3& translate) { m_translate = translate; }

const glm::vec3& Transformation::getTranslate() const { return m_translate; }

void Transformation::setScale(const glm::vec3& scale)
{
    if ((scale.x == scale.y) && (scale.x == scale.z))
        setUniformScale(scale.x);
    else
        m_scale = scale;
}

const glm::vec3& Transformation::getScale() const { return m_scale; }

void Transformation::setUniformScale(const float scale)
{
    m_isUniformScale = true;
    m_scale = glm::vec3{scale, scale, scale};
}

float Transformation::getUniformScale() const
{
    assert(m_isUniformScale);
    return m_scale.x;
}

float Transformation::getNorm() const { return 0.f; }

void Transformation::makeIdentity() {}

void Transformation::makeUnitScale() {}

bool Transformation::isIdentity() const { return m_isIdentity; }

bool Transformation::isRSMatrix() const { return m_isRSMatrix; }

bool Transformation::isUniformScale() const { return m_isUniformScale; }

glm::vec3 Transformation::applyForward(const glm::vec3& in)
{
    if (isIdentity())
        return in;

    if (isRSMatrix())
    {
        // Y = R * S * X + T
        auto out = glm::vec3{m_scale.x * in.x, m_scale.y * in.y, m_scale.z * in.z};
        return m_matrix * out + m_translate;
    }

    // Y = M * X + T
    return m_matrix * in + m_translate;
}

void Transformation::applyForward(size_t count, const glm::vec3* in, glm::vec3* out) {}

Plane3 Transformation::applyForward(const Plane3& in) const { return in; }

glm::vec3 Transformation::applyInverse(const glm::vec3& in)
{
    if (isIdentity())
        return in;

    // (Y - T)
    auto out = in - m_translate;
    if (isRSMatrix())
    {
        // X = S^(-1) * R^t * (Y - T)
        out = out * m_matrix;
        if (isUniformScale())
        {
            out /= getUniformScale();
        }
        else
        {
            auto sxy = m_scale.x * m_scale.y;
            auto sxyz = sxy * m_scale.z;

            auto sxyzInv = 1.f / sxyz;
            auto sxyInv = sxyzInv * m_scale.z;

            out.x *= sxyInv * m_scale.y;
            out.y *= sxyInv * m_scale.x;
            out.z *= sxyzInv * sxy;
        }
        return out;
    }

    // X = M^(-1) * (Y - T)
    return glm::inverse(m_matrix) * out;
}

void Transformation::applyInverse(size_t count, const glm::vec3* in, glm::vec3* out) {}

void Transformation::product(const Transformation& a, const Transformation& b) {}

void Transformation::inverse(const Transformation& inverse) {}

glm::vec3 Transformation::invertVector(const glm::vec3& in) { return in; }