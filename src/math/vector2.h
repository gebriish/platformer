#pragma once
#include "types.h"

namespace ENGINE::MATH
{
	struct vector2 {
		f32 x, y;

		vector2(f32 x_val = 0.0f, f32 y_val = 0.0f) : x(x_val), y(y_val) {}

		vector2 operator+(const vector2& other) const {
			return vector2(x + other.x, y + other.y);
		}

		vector2 operator-(const vector2& other) const {
			return vector2(x - other.x, y - other.y);
		}

		vector2 operator*(f32 scalar) const {
			return vector2(x * scalar, y * scalar);
		}

		vector2 operator/(f32 scalar) const {
			return vector2(x / scalar, y / scalar);
		}

		vector2& operator+=(const vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		vector2& operator-=(const vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		vector2& operator*=(f32 scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}

		vector2& operator/=(f32 scalar) {
			x /= scalar;
			y /= scalar;
			return *this;
		}

		bool operator==(const vector2& other) const {
			return x == other.x && y == other.y;
		}

		bool operator!=(const vector2& other) const {
			return !(*this == other);
		}
	};


	vector2 lerp(const vector2& a, const vector2& b, float t);
	f32 dot(const vector2& a, const vector2& b);
	f32 length(const vector2& v) ;
	vector2 normalize(const vector2& v);
}