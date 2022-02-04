#include "AdditionFunctions/Addition.h"
#include "SubtractionFunctions/Subtract.h"
#include "MultiplyFunctions/Multiply.h"
#include "DivideFunctions/Divide.h"
#include "AllMath.h"

namespace MathLibrary::AllMath {

	float AllMath::test_add(const float val1, const float val2) {
		return Addition::AdditionClass::add(val1, val2);
	}

	float AllMath::test_subtract(const float val1, const float val2) {
		return Subtract::SubtractionClass::subtract(val1, val2);
	}

	float AllMath::test_multiply(const float val1, const float val2) {
		return Multiply::MultiplicationClass::multiply(val1, val2);
	}

	float AllMath::test_divide(const float val1, const float val2) {
		return Divide::DivisionClass::division(val1, val2);
	}

}