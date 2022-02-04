#include <iostream>
// This file can see the libmath folder
#include "libmath/AllMath/AllMath.h"

int main() {
	std::cout << MathLibrary::AllMath::AllMath::test_add(1, 1) << std::endl;
}