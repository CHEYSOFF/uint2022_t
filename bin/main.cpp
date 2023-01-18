
#include <iostream>
#include "../lib/number.cpp"

int main() {
    uint2022_t value = from_string("1367243623268231712");
    uint2022_t value2 = from_string("73423151215215215");
    std::cout << value << "\n";
    std::cout << value2 << "\n";
    std::cout << value % value2;

    return 0;
}
