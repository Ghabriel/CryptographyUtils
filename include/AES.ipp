
template<typename T>
T crypto::AES::internalApply(T message, const Key& key, size_t rounds) const {
	// TODO
	return message;
}

std::vector<crypto::AES::Word> crypto::AES::keyExpansion(const Key& key) const {
	std::vector<Word> result;
	result.reserve(44);

	// for (size_t i = 0; i < 4; i++) {
	// 	result.push_back(key & (0xFF000000 >> (8 * i)));
	// }

	// for (size_t i = 4; i < 44; i++) {
	// 	Word aux = result.back();
	// 	if (i % 4 == 0) {
	// 		// aux = substWord(rotateWord(aux)) ^q
	// 	}

	// 	result.push_back(result[i - 4] ^ aux);
	// }
	return result;
}
