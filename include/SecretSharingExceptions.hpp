#ifndef SECRET_SHARING_EXCEPTIONS
#define SECRET_SHARING_EXCEPTIONS

#include <stdexcept>

namespace crypto {
    class InsufficientPartsException : public std::runtime_error {
     public:
        InsufficientPartsException(NumberView expected, NumberView actual)
         : std::runtime_error(
            "Insufficient number of parts (expected " +
            std::to_string(expected) + ", got " +
            std::to_string(actual) + ")") {}
    };
}

#endif
