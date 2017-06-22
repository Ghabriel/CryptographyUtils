#include "debug.hpp"
#include "ShamirScheme.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
    using crypto::ShamirScheme;

    // auto scheme = ShamirScheme(3, 6, 999999999);
    // auto parts = scheme.split(1234);
    // XTRACE(parts);
    // XTRACE(scheme.reconstruct({parts[1], parts[3], parts[4]}));

    auto scheme = ShamirScheme(2, 5, 521);
    auto parts = scheme.split(512);
    XTRACE(parts);
    XTRACE(scheme.reconstruct({parts[0], parts[3]}));
}
