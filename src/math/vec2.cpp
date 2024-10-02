#include "vec2.h"
#include <cmath>

namespace ENGINE::MATH
{

    vec2::vec2()
        : x(0.0), y(0.0)
    {}

    vec2::vec2(f32 d)
        : x(d), y(d)
    {}

    vec2::vec2(f32 v0, f32 v1)
        : x(v0), y(v1)
    {}

    
    f32 dot(const vec2& a, const vec2& b) 
    {
        return a.x * b.x + a.y * b.y;
    }

    f32 length(const vec2& v)
    {
        return std::sqrt(dot(v, v));
    }

    vec2 normalize(const vec2& v)
    {
        float l = length(v);
        if(l > 0)
            return v/l;
        else return vec2(0);
    }

    vec2 lerp(const vec2& a, const vec2& b, float t)
    {
        return a + (b - a) * t;
    }
}
