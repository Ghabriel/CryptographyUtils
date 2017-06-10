#include "debug.hpp"
#include "ChineseRemainder.hpp"
#include "traits.hpp"
#include "xtrace.hpp"

using crypto::Number;

int main(int, char**) {
    using crypto::ChineseRemainder;

    ChineseRemainder calculator;
    calculator.push(2, 3);
    calculator.push(3, 5);
    calculator.push(2, 7);

    TRACE(calculator.eval());
}
