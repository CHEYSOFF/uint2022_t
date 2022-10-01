#include "number.h"
#include <cstring>
#include <string>
uint2022_t from_uint(uint32_t i)
{
    uint2022_t a;
    a.num[0] = i;
    return a;
}

uint2022_t from_string(const char *buff)
{
    uint2022_t a;
    uint64_t tmp = 0;
    int cur = 0;
    for (int i = 0; i < strlen(buff); i++)
    {
        int c = buff[i] - '0';
        tmp *= 10;
        tmp += c;

        // std::cout << tmp << "\n";
        // std::cout << a.radix << "\n";
        if (tmp > a.radix)
        {
            // std::cout<<tmp<<"\n";
            a.num[cur] = tmp % a.radix;
            tmp /= a.radix;
            cur++;
            if (cur >= a.size)
                return a;
        }
    }
    a.num[cur] = tmp;
    // std::cout << cur << "\n";
    // std::cout << a.num[0] << " " << a.num[1] << "\n";
    return a;
}

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs)
{
    return uint2022_t();
}

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs)
{
    return uint2022_t();
}

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs)
{
    return uint2022_t();
}

uint2022_t operator*(const uint2022_t &lhs, const uint64_t &k)
{
    uint64_t carry = 0;
    // uint64_t tmp=0;
    uint2022_t new_num;
    for (int i = 0; i < new_num.size; i++)
    {
        uint64_t tmp = lhs.num[i] * k + carry;
        new_num.num[i] = tmp % new_num.radix;
        carry = tmp / new_num.radix;
    }

    return new_num;
}

uint2022_t operator/(const uint2022_t &lhs, const uint2022_t &rhs)
{

    return uint2022_t();
}

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs)
{
    return false;
}

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs)
{
    return false;
}

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value)
{

    for(int i = 0; i < value.size; i++){
        stream << value.num[i] << " ";
    }

    return stream;
}
