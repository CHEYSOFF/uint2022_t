#pragma once
#include <cinttypes>
#include <iostream>

struct uint2022_t {
    uint32_t num[68];
    uint32_t size = 68;
    uint32_t radix = 1000000000;
    uint32_t digit_len = 9;
    // wanted to make size, radix and digit_len constant, but if so,
    // you can't equate uint2022_t to another uint2022_t after creating it
    uint2022_t() {
        for (int i = 0; i < size; i++) {
            num[i] = 0;
        }
    }
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char *buff);

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs);

void operator+=(uint2022_t &lhs, const uint2022_t &rhs);

void operator++(uint2022_t &lhs);

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs);

void operator-=(uint2022_t &lhs, const uint2022_t &rhs);

void operator--(uint2022_t &lhs);

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs);

void operator*=(uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator/(const uint2022_t &lhs, const uint2022_t &rhs);

void operator/=(uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator%(const uint2022_t &lhs, const uint2022_t &rhs);

void operator%=(uint2022_t &lhs, const uint2022_t &rhs);

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator>(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator>=(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator<(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator<=(const uint2022_t &lhs, const uint2022_t &rhs);

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value);
