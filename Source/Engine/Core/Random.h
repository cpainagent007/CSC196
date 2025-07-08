#pragma once
#include <cstdlib>

namespace Cpain {
	namespace CRandom {

		inline int getRandomInt() { return rand(); }
		inline int getRandomInt(int max) { return rand() % max; }
		inline int getRandomInt(int min, int max) { return min + getRandomInt(max - min + 1); }

		inline float getRandomFloat() { return rand() / static_cast<float>(RAND_MAX); }

	}
	
}