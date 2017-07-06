#include <limits>

#include "debug.hpp"
#include "AES.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
    using crypto::AES;

    auto aes = AES();

    auto plaintext = AES::input128{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 129};
    XTRACE(plaintext);

    auto key = AES::input128{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127};
    XTRACE(key);

    auto encrypted = aes.apply(plaintext, key);
    XTRACE(encrypted);
}
