#pragma once
#include <types.h>

namespace ENGINE::MATH
{
    class vec2
    {
    public:
        vec2();
        vec2(f32 d);
        vec2(f32 v0, f32 v1);

        // Addition operator
        vec2 operator+(const vec2& other) const
        {
            return vec2(x + other.x, y + other.y);
        }

        // Subtraction operator
        vec2 operator-(const vec2& other) const
        {
            return vec2(x - other.x, y - other.y);
        }

        // Multiplication by scalar
        vec2 operator*(f32 scalar) const
        {
            return vec2(x * scalar, y * scalar);
        }

        // Division by scalar
        vec2 operator/(f32 scalar) const
        {
            return vec2(x / scalar, y / scalar);
        }

        // Compound assignment addition
        vec2& operator+=(const vec2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        // Compound assignment subtraction
        vec2& operator-=(const vec2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // Compound assignment multiplication by scalar
        vec2& operator*=(f32 scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        // Compound assignment division by scalar
        vec2& operator/=(f32 scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        // Negation operator
        vec2 operator-() const
        {
            return vec2(-x, -y);
        }

        // Equality operator
        bool operator==(const vec2& other) const
        {
            return x == other.x && y == other.y;
        }

        // Inequality operator
        bool operator!=(const vec2& other) const
        {
            return !(*this == other);
        }

        float x, y;
    };
    
    f32 dot(const vec2& a, const vec2& b);
    f32 length(const vec2& v);
    vec2 normalize(const vec2& v);
}
