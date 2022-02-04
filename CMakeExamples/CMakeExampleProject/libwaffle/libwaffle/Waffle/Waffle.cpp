#include "Waffle.h"
#include <iostream>

namespace WaffleLibrary::Waffle {
	Waffle::Waffle(const int qty)
		:m_qty{qty} {
	}

	void Waffle::hungry() const {
		std::cout << "I'm hungry, I'm going to eat " << m_qty << "waffles!" << std::endl;;
	}
} // namespace WaffleLibrary::Waffle