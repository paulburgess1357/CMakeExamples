#include "Pancake.h"

namespace WaffleLibrary::Pancake {

	Pancake::Pancake(const int qty)
		:m_qty{ qty } {
	}

	void Pancake::hungry() const {
		std::cout << "I'm hungry, I'm going to eat " << m_qty << "pancakes!" << std::endl;;
	}

} // namespace WaffleLibrary::Pancake