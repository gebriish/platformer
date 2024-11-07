#pragma once
#include <iostream>
#include <string>

struct vec3 {
	vec3();
	vec3(float d);
	vec3(float x, float y, float z); 

	vec3& operator=(const vec3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    vec3& operator+=(const vec3& other) {
        x += other.x;
        y += other.y;
		z += other.z;
        return *this;
    }

    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    vec3& operator-=(const vec3& other) {
        x -= other.x;
        y -= other.y;
		z -= other.z;
        return *this;
    }

    vec3 operator*(float scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    vec3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
		z *= scalar;
        return *this;
    }

    vec3 operator/(float scalar) const {
        return vec3(x / scalar, y / scalar, z / scalar);
    }

    vec3& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
		z /= scalar;
        return *this;
    }

    bool operator==(const vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const vec3& other) const {
        return !(*this == other);
    }

    vec3 operator-() const {
        return vec3(-x, -y, -z);
    }

	float x, y, z;
};

float dot(const vec3& a, const vec3& b);
float length(const vec3& vec);
vec3 normalize(const vec3& vec);
vec3 lerp(const vec3& a, const vec3& b, float t);
