#include "debug.hpp"
#include "xtrace.hpp"

crypto::ByteSequence crypto::detail::decompose(const std::string& message) {
	std::vector<uint8_t> result;
	result.reserve(message.size());

	for (char c : message) {
		result.push_back(c);
	}

	XTRACE(result);
	return result;
}

template<typename T>
std::string crypto::ElectronicCodebook::encrypt(const std::string& message,
	const T& key) const {

	// auto bytes = detail::decompose(message);
	// ByteSequence result;
	// result.reserve(bytes.size());

	// while (bytes.size() > 0) {
	// 	result.push_back(algorithm.apply(bytes));
	// }

	return message;
}
