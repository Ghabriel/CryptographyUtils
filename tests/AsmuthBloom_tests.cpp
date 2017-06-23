#include "debug.hpp"
#include "AsmuthBloom.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
    using crypto::AsmuthBloom;

    // auto scheme = AsmuthBloom(3, 6, 999999999);
    // auto parts = scheme.split(1234);
    // XTRACE(parts);
    // XTRACE(scheme.reconstruct({parts[1], parts[3], parts[4]}));

    auto scheme = AsmuthBloom(2, 5);
    auto data = scheme.split(10);
    XTRACE(data);
    auto& m0 = data.first;
    auto& parts = data.second;
    XTRACE(scheme.reconstruct(m0, {parts[0], parts[3]}));
}
