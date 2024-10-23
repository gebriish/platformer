#pragma once
#include <iostream>
#include <string>

struct vec2 {
	vec2();
	vec2(float d);
	vec2(float x, float y); 

	vec2& operator=(const vec2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2& operator+=(const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }

    vec2& operator-=(const vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    vec2 operator*(float scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    vec2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    vec2 operator/(float scalar) const {
        return vec2(x / scalar, y / scalar);
    }

    vec2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const vec2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const vec2& other) const {
        return !(*this == other);
    }

    vec2 operator-() const {
        return vec2(-x, -y);
    }

	float x, y;
};

float dot(const vec2& a, const vec2& b);
float length(const vec2& vec);
vec2 normalize(const vec2& vec);
