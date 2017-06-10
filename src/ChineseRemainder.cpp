#include <tuple>
#include "debug.hpp"
#include "ChineseRemainder.hpp"

using crypto::Number;

void crypto::ChineseRemainder::push(NumberView a, NumberView n) {
	data.push_back({a, n});
}

Number crypto::ChineseRemainder::eval() const {
	auto pairs = data;
	while (pairs.size() > 1) {
		auto& n1 = pairs[0].second;
		auto& n2 = pairs[1].second;
		auto params = xgcd(n1, n2);

		auto& a1 = pairs[0].first;
		auto& a2 = pairs[1].first;
		auto x = a1 * std::get<1>(params) * n2 + a2 * std::get<0>(params) * n1;

		pairs.pop_front();
		pairs.pop_front();
		pairs.push_front({x, n1 * n2});
	}

	auto& result = pairs[0].first;

	if (result < 0) {
		result += pairs[0].second;
	}

	return result;
}
