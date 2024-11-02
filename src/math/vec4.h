#pragma once
#include <iostream>
#include <string>

struct vec4 {
	vec4();
	vec4(float d);
	vec4(float x, float y, float z, float w); 

	vec4& operator=(const vec4& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    vec4 operator+(const vec4& other) const {
        return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    vec4& operator+=(const vec4& other) {
        x += other.x;
        y += other.y;
		z += other.z;
		w += other.w;
        return *this;
    }

    vec4 operator-(const vec4& other) const {
        return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    vec4& operator-=(const vec4& other) {
        x -= other.x;
        y -= other.y;
		z -= other.z;
		w -= other.w;
        return *this;
    }

    vec4 operator*(float scalar) const {
        return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    vec4& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
		z *= scalar;
		w *= scalar;
        return *this;
    }

    vec4 operator/(float scalar) const {
        return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    vec4& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
		z /= scalar;
		w /= scalar;
        return *this;
    }

    bool operator==(const vec4& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool operator!=(const vec4& other) const {
        return !(*this == other);
    }

    vec4 operator-() const {
        return vec4(-x, -y, -z, -w);
    }

	float x, y, z, w;
};

float dot(const vec4& a, const vec4& b);
float length(const vec4& vec);
vec4 normalize(const vec4& vec);
