#include <unordered_set>
#include "primality/MillerRabin.hpp"

bool crypto::MillerRabin::test(NumberView n, NumberView accuracy) const {
	if (n < 3 || n % 2 == 0) {
		return (n == 2);
	}

	std::unordered_set<Number> bases;
	auto size = std::min(accuracy, n - 3);
	while (bases.size() < size) {
		bases.insert(random(2, n - 1));
	}

	return internalTest(n, bases);
}
