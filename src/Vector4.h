#ifndef __VECTOR_4_H__
#define __VECTOR_4_H__

#include <math.h>

class Vector4
{
public:
    Vector4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
    Vector4() : m_x(0), m_y(0), m_z(0), m_w(0) {}
    float getX() { return m_x; }
    float getY() { return m_y; }
    float getZ() { return m_z; }
    float getW() { return m_w; }
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }
    void setZ(float z) { m_z = z; }
    void setW(float w) { m_w = w; }
    float length() { return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w); }

    Vector4 operator+(const Vector4 &vector2) const
    {
        return Vector4(
            m_x + vector2.m_x,
            m_y + vector2.m_y,
            m_z + vector2.m_z,
            m_w + vector2.m_w);
    }

    Vector4 &operator+=(const Vector4 &vector2)
    {
        m_x += vector2.m_x;
        m_y += vector2.m_y;
        m_z += vector2.m_z;
        m_w += vector2.m_w;
        return *this;
    }

    Vector4 operator*(float scalar)
    {
        return Vector4(
            m_x * scalar,
            m_y * scalar,
            m_z * scalar,
            m_w * scalar);
    }

    Vector4 &operator*=(float scalar)
    {
        m_x *= scalar;
        m_y *= scalar;
        m_z *= scalar;
        m_w *= scalar;
        return *this;
    }

    Vector4 operator-(const Vector4 &vector2) const
    {
        return Vector4(
            m_x - vector2.m_x,
            m_y - vector2.m_y,
            m_z - vector2.m_z,
            m_w - vector2.m_w);
    }

    Vector4 &operator-=(const Vector4 &vector2)
    {
        m_x -= vector2.m_x;
        m_y -= vector2.m_y;
        m_z -= vector2.m_z;
        m_w -= vector2.m_w;
        return *this;
    }

    Vector4 operator/(float scalar)
    {
        return Vector4(
            m_x / scalar,
            m_y / scalar,
            m_z / scalar,
            m_w / scalar

        );
    }

    Vector4 &operator/=(float scalar)
    {
        m_x /= scalar;
        m_y /= scalar;
        m_z /= scalar;
        m_w /= scalar;
        return *this;
    }

    // Cross product in three dimensional subspace
    Vector4 operator^(Vector4 vector2)
    {
        return Vector4(
            m_y * vector2.m_z - m_z * vector2.m_y,
            m_z * vector2.m_x - m_x * vector2.m_z,
            m_x * vector2.m_y - m_y * vector2.m_x,
            m_w);
    }

    Vector4 &operator^=(Vector4 &vector2)
    {
        float x = m_x, y = m_y, z = m_z;
        m_x = y * vector2.m_z - z * vector2.m_y;
        m_y = z * vector2.m_x - x * vector2.m_z;
        m_z = x * vector2.m_y - y * vector2.m_x;
        return *this;
    }

    // Dot product
    float operator*(Vector4 vector2)
    {
        return 
        m_x * vector2.m_x +
        m_y * vector2.m_y +
        m_z * vector2.m_z +
        m_w * vector2.m_w;
    }

    void normalize()
    {
        float l = length();
        if (l > 0)
        {
            (*this) *= 1 / l;
        }
    }

private:
    float m_x;
    float m_y;
    float m_z;
    float m_w;
};

typedef Vector4 Point;
typedef Vector4 Color;

#endif