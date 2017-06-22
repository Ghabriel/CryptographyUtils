#include "AsmuthBloom.hpp"

using PartGroup = crypto::AsmuthBloom::PartGroup;

crypto::AsmuthBloom::AsmuthBloom(NumberView k, NumberView n) : k(k), n(n) {}

PartGroup crypto::AsmuthBloom::split(NumberView secret) {
	std::vector<Number> m;
	m.reserve(n);
	
}
