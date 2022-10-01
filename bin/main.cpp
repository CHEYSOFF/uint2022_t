
#include <iostream>
#include "../lib/number.cpp"

int main()
{
    uint2022_t value = from_string("100000000");
    std::cout << value << '\n';
    std::cout << value * 1987;
    // std::cout<<value.num[63];
    // std::cout << value << std::endl;
    // long long a=(1ll<<32-1);
    // std::cout<<a;
    return 0;
}
