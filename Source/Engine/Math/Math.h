#pragma once
#include <algorithm>
#include <cmath>

namespace Cpain {
	namespace CMath {

		constexpr float pi = 3.14159265359f;
		constexpr float twoPi = 2 * pi;
		constexpr float halfPi = pi / 2;

		constexpr float radToDeg(float rad) { return rad * (180 / pi); }
		constexpr float degToRad(float deg) { return deg * (pi / 180); }

		using std::min;
		using std::max;
		using std::clamp;

		using std::sqrt;
		using std::sqrtf;

		using std::sin;
		using std::sinf;

		using std::cos;
		using std::cosf;

		using std::tan;
		using std::tanf;
	}
}