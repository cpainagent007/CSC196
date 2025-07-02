#include <iostream>
#include "Math/Math.h"
#include "Core/Random.h"

int main(){
	std::cout << "Hello, World!\n";
	std::cout << Cpain::CMath::pi << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << Cpain::CRandom::getRandomInt(5) << std::endl;
	}
}