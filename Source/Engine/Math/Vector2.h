#pragma once
#include "Math.h"

namespace Cpain {
	namespace CVec2 {
		template<typename T>
		struct Vector2 {

			T x, y;

			Vector2() = default;
			Vector2(T x, T y) : x{ x }, y{ y } {}

			Vector2 operator+(const Vector2& value) const { return Vector2{ x + value.x, y + value.y }; }
			Vector2 operator-(const Vector2& value) const { return Vector2{ x - value.x, y - value.y }; }
			Vector2 operator*(const T& value) const { return Vector2{ x * value, y * value }; }
			Vector2 operator/(const T& value) const { return Vector2{ x / value, y / value }; }

			Vector2 operator+(float scalar) const { return Vector2{ x + scalar, y + scalar }; }
			Vector2 operator-(float scalar) const { return Vector2{ x - scalar, y - scalar }; }
			Vector2 operator*(float scalar) const { return Vector2{ x * scalar, y * scalar }; }
			Vector2 operator/(float scalar) const { return Vector2{ x / scalar, y / scalar }; }

			Vector2& operator+=(const Vector2& value) { x += value.x; y += value.y; return *this; }
			Vector2& operator-=(const Vector2& value) { x -= value.x; y -= value.y; return *this; }
			Vector2& operator*=(const T& value) { x *= value; y *= value; return *this; }
			Vector2& operator/=(const T& value) { x /= value; y /= value; return *this; }

			Vector2& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
			Vector2& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
			Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
			Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

			T operator[](unsigned int index) const { return (&x)[index]; }
			T& operator[](unsigned int index) { return (&x)[index]; }

			float lengthSqrd() const { return (x * x) + (y * y); }
			float length() const { return Cpain::CMath::sqrtf(lengthSqrd()); }

		};

		using ivec2 = Vector2<int>;
		using vec2 = Vector2<float>;
	}
}