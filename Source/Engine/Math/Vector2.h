#pragma once
#include "Math.h"

namespace Cpain {
	namespace CVec2 {
		template<typename T>
		struct Vector2 {

			union {
				struct { T x, y; };
				struct { T u, v; };
			};

			Vector2() = default;
			Vector2(T x, T y) : x{ x }, y{ y } {}

			Vector2 operator+(const Vector2& value) const { return Vector2{ x + value.x, y + value.y }; }
			Vector2 operator-(const Vector2& value) const { return Vector2{ x - value.x, y - value.y }; }
			//Vector2 operator*(const T& value) const { return Vector2{ x * value, y * value }; }
			//Vector2 operator/(const T& value) const { return Vector2{ x / value, y / value }; }

			Vector2 operator+(float scalar) const { return Vector2{ x + scalar, y + scalar }; }
			Vector2 operator-(float scalar) const { return Vector2{ x - scalar, y - scalar }; }
			Vector2 operator*(float scalar) const { return Vector2{ x * scalar, y * scalar }; }
			Vector2 operator/(float scalar) const { return Vector2{ x / scalar, y / scalar }; }

			Vector2& operator+=(const Vector2& value) { x += value.x; y += value.y; return *this; }
			Vector2& operator-=(const Vector2& value) { x -= value.x; y -= value.y; return *this; }
			//Vector2& operator*=(const T& value) { x *= value; y *= value; return *this; }
			//Vector2& operator/=(const T& value) { x /= value; y /= value; return *this; }

			Vector2& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
			Vector2& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
			Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
			Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

			T operator[](unsigned int index) const { return (&x)[index]; }
			T& operator[](unsigned int index) { return (&x)[index]; }

			/// <summary>
			/// Calculates the squared length (magnitude) of a 2D vector.
			/// </summary>
			/// <returns>The sum of the squares of the x and y components, representing the squared length of the vector.</returns>
			float lengthSqrd() const { return (x * x) + (y * y); }

			/// <summary>
			/// Calculates the length (magnitude) using the square root of the squared length.
			/// </summary>
			/// <returns>The length as a floating-point value.</returns>
			float length() const { return Cpain::CMath::sqrtf(lengthSqrd()); }

			/// <summary>
			/// Returns a normalized (unit length) version of the vector.
			/// </summary>
			/// <returns>A Vector2 representing the original vector scaled to have a length of 1.</returns>
			Vector2 normalized() const { return *this / length(); }

			/// <summary>
			/// Returns the angle in radians between the positive x-axis and the point (x, y).
			/// </summary>
			/// <returns>The angle in radians, computed using atan2f(y, x).</returns>
			float angle() const { return Cpain::CMath::atan2f(y, x); }

			/// <summary>
			/// Returns a new Vector2 that is the result of rotating this vector by a specified angle in radians.
			/// </summary>
			/// <param name="radians">The angle to rotate the vector, in radians.</param>
			/// <returns>A new Vector2 representing the rotated vector.</returns>
			Vector2 rotate(float radians) const { 
				Vector2 v;

				v.x = x * Cpain::CMath::cosf(radians) - y * Cpain::CMath::sinf(radians);
				v.y = x * Cpain::CMath::sinf(radians) + y * Cpain::CMath::cosf(radians);

				return v;
			}

		};

		using ivec2 = Vector2<int>;
		using vec2 = Vector2<float>;
	}
}