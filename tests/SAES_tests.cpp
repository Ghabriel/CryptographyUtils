#include <limits>

#include "debug.hpp"
#include "SAES.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
    using crypto::SAES;

    auto saes = SAES();

    auto plaintext = 129;
    TRACE(plaintext);

    auto key = 127;
    TRACE(key);

    auto encrypted = saes.apply(plaintext, key);
    TRACE(encrypted);
}
