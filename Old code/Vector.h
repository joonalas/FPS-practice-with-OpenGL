#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector {
    public:
        Vector(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
        Vector() : m_x(0), m_y(0), m_z(0) {}
        float getX() {return m_x;}
        float getY() {return m_y;}
        float getZ() {return m_z;}
        void setX(float x) {m_x = x;}
        void setY(float y) {m_y = y;}
        void setZ(float z) {m_z = z;}
        float length() { return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);}

        Vector operator +(const Vector& vector2) const {
            return Vector(m_x + vector2.m_x, m_y + vector2.m_y, m_z + vector2.m_z);
        }

        Vector& operator +=(const Vector& vector2) {
            m_x += vector2.m_x;
            m_y += vector2.m_y;
            m_z += vector2.m_z;
            return *this;
        }

        Vector operator *(float scalar) {
            return Vector(m_x * scalar, m_y * scalar, m_z * scalar);
        }

        Vector& operator *=(float scalar) {
            m_x *= scalar;
            m_y *= scalar;
            m_z *= scalar;
            return *this;
        }

        Vector operator -(const Vector& vector2) const {
            return Vector(m_x - vector2.m_x, m_y - vector2.m_y, m_z - vector2.m_z);
        }

        Vector& operator -=(const Vector& vector2) {
            m_x -= vector2.m_x;
            m_y -= vector2.m_y;
            m_z -= vector2.m_z;
            return *this;
        }

        Vector operator /(float scalar) {
            return Vector(m_x / scalar, m_y / scalar, m_z / scalar);
        }

        Vector& operator /=(float scalar) {
            m_x /= scalar;
            m_y /= scalar;
            m_z /= scalar;
            return *this;
        }

        Vector operator ^(Vector vector2)
        {
            return Vector(
                m_y * vector2.m_z - m_z * vector2.m_y,
                m_z * vector2.m_x - m_x * vector2.m_z,
                m_x * vector2.m_y - m_y * vector2.m_x
            );
        }

        void normalize() {
            float l = length();
            if(l>0) {
                (*this) *= 1 / l;
            }
        }

    private:
        float m_x;
        float m_y;
        float m_z;
};

#endif