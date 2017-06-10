#ifndef CHINESE_REMAINDER_HPP
#define CHINESE_REMAINDER_HPP

#include <deque>
#include "traits.hpp"
#include "utils.hpp"

namespace crypto {
    class ChineseRemainder {
     public:
        void push(NumberView a, NumberView n);
        Number eval() const;

     private:
        std::deque<std::pair<Number, Number>> data;
    };
}

#endif
