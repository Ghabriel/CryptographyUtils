#include <limits>

#include "debug.hpp"
#include "operation_modes/ElectronicCodebook.hpp"
#include "SAES.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
	using crypto::ElectronicCodebook;
    using crypto::SAES;

    auto ecb = ElectronicCodebook(SAES());

    auto plaintext = "Hello, world!";
    TRACE(plaintext);

    auto key = 127;
    TRACE(key);

    auto encrypted = ecb.encrypt(plaintext, key);
    TRACE(encrypted);
}
