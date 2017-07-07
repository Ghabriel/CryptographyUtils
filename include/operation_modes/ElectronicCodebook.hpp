#ifndef ELECTRONIC_CODEBOOK_HPP
#define ELECTRONIC_CODEBOOK_HPP

#include <string>
#include <vector>
#include "SAES.hpp"

namespace crypto {
    using ByteSequence = std::vector<uint8_t>;
    namespace detail {
        ByteSequence decompose(const std::string&);
    }

    class ElectronicCodebook {
    public:
        // TODO: use a template
        explicit ElectronicCodebook(SAES algorithm) : algorithm(algorithm) {}
        template<typename T>
        std::string encrypt(const std::string& message, const T& key) const;

    private:
        SAES algorithm;
    };
}

#include "ElectronicCodebook.ipp"

#endif
