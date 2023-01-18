#include "number.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>

uint2022_t max_num = from_string("481560916771158684800786922703235625631274322714142263414417884163925873322306437689024231009526751394401758326916367106052034484602375642882110959089521812209947069992139877256008949136579813164413834190131240610432508865633901300457687591589632190325582710683886781973951695733384278544896131740867054246692573031629150247882082682647773168904426336814855367810693467547461780797071163567159452928068892906992787178135839959347223507647240845924670958716173279750751341651541295792537288393481542519773223140547524361834615428274169543954961376881442030303829940191406452725012875774576546969913778507874304");
// max_num = 2**2022
// There is a way to make right number more obvius, but then you need to multiply it by 2 2022 times
// It takes a lot of time, because after the multiplication we COPY the result to a number

uint2022_t from_uint(uint32_t i) {
    uint2022_t a;
    for (int32_t j = 0; j < a.size; j++) {
        a.num[j] = i % a.radix;
        i /= a.radix;
        if (i == 0) {
            break;
        }
    }
    return a;
}

uint2022_t from_string(const char *buff) {
    uint2022_t a;
    int32_t cur = 0;
    for (int32_t i = strlen(buff) - 1; i >= 0; i -= a.digit_len) {
        for (int32_t j = std::max(static_cast<int32_t>(i - a.digit_len + 1), 0); j <= i; j++) {
            a.num[cur] *= 10;
            a.num[cur] += buff[j] - '0';
        }

        cur++;
    }

    return a;
}

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint64_t carry = 0;
    uint2022_t new_num;
    for (int32_t i = 0; i < new_num.size; i++) {
        uint64_t tmp = lhs.num[i] + rhs.num[i] + carry;
        new_num.num[i] = tmp % new_num.radix;
        carry = tmp / new_num.radix;
    }

    return new_num;
}

void operator+=(uint2022_t &lhs, const uint2022_t &rhs) {
    uint64_t carry = 0;
    for (int32_t i = 0; i < lhs.size; i++) {
        uint64_t tmp = lhs.num[i] + rhs.num[i] + carry;
        lhs.num[i] = tmp % lhs.radix;
        carry = tmp / lhs.radix;
    }
}

void operator++(uint2022_t &lhs) {
    lhs += from_uint(1);
}

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint64_t carry = 0;
    uint2022_t new_num;
    for (int32_t i = 0; i < new_num.size; i++) {
        int64_t tmp = lhs.num[i] + carry;
        carry = 0;

        if (lhs.num[i] + carry < rhs.num[i]) {
            carry -= 1;
            tmp += new_num.radix;
        }
        tmp -= rhs.num[i];
        new_num.num[i] = tmp % new_num.radix;
    }

    return new_num;
}

void operator-=(uint2022_t &lhs, const uint2022_t &rhs) {
    uint64_t carry = 0;
    for (int32_t i = 0; i < lhs.size; i++) {
        int64_t tmp = lhs.num[i] + carry;
        carry = 0;

        if (lhs.num[i] + carry < rhs.num[i]) {
            carry -= 1;
            tmp += lhs.radix;
        }
        tmp -= rhs.num[i];
        lhs.num[i] = tmp % lhs.radix;
    }
}

void operator--(uint2022_t &lhs) {
    lhs -= from_uint(1);
}

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t new_num;
    for (int32_t i = 0; i < new_num.size; i++) {
        for (int32_t j = 0; j < new_num.size; j++) {
            uint64_t carry = uint64_t(rhs.num[i]) * uint64_t(lhs.num[j]);

            for (int32_t k = i + j; k < new_num.size; k++) {
                if (carry == 0 && new_num.num[k] < new_num.radix) {
                    break;
                }
                carry += new_num.num[k];
                new_num.num[k] = carry % new_num.radix;
                carry /= new_num.radix;
            }
        }
    }

    return new_num;
}

void operator*=(uint2022_t &lhs, const uint2022_t &rhs) {
    for (int32_t i = 0; i < lhs.size; i++) {
        for (int32_t j = 0; j < lhs.size; j++) {
            uint64_t carry = uint64_t(rhs.num[i]) * uint64_t(lhs.num[j]);

            for (int32_t k = i + j; k < lhs.size; k++) {
                if (carry == 0 && lhs.num[k] < lhs.radix) {
                    break;
                }
                carry += lhs.num[k];
                lhs.num[k] = carry % lhs.radix;
                carry /= lhs.radix;
            }
        }
    }
}

uint2022_t operator/(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t new_int;

    uint2022_t tmp_lhs = lhs;

    while (tmp_lhs >= rhs) {
        uint2022_t tmp_rhs = rhs;
        uint32_t degree = 0;
        while (tmp_lhs > tmp_rhs) {
            degree++;
            tmp_rhs = tmp_rhs * from_uint(10);
        }
        degree--;
        uint2022_t tmp_diff = rhs;
        uint2022_t multiplier = from_uint(1);
        for (int32_t i = 0; i < degree / new_int.digit_len; i++) {
            multiplier = multiplier * from_uint(1000000000);
        }
        for (int32_t i = 0; i < degree % new_int.digit_len; i++) {
            multiplier = multiplier * from_uint(10);
        }
        tmp_diff = tmp_diff * multiplier;
        while (tmp_lhs >= tmp_diff) {
            tmp_lhs = tmp_lhs - tmp_diff;

            new_int = new_int + multiplier;
        }
    }

    return new_int;
}

uint2022_t operator%(const uint2022_t &lhs, const uint2022_t &rhs) {
    return lhs - (lhs / rhs) * rhs;
}

void operator%=(uint2022_t &lhs, const uint2022_t &rhs) {
    lhs -= (lhs / rhs) * rhs;
}

void operator/=(uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t tmp_lhs = lhs;

    while (tmp_lhs >= rhs) {
        uint2022_t tmp_rhs = rhs;
        uint32_t degree = 0;
        while (tmp_lhs > tmp_rhs) {
            degree++;
            tmp_rhs = tmp_rhs * from_uint(10);
        }
        degree--;
        uint2022_t tmp_diff = rhs;
        uint2022_t multiplier = from_uint(1);
        for (int32_t i = 0; i < degree / lhs.digit_len; i++) {
            multiplier = multiplier * from_uint(1000000000);
        }
        for (int32_t i = 0; i < degree % lhs.digit_len; i++) {
            multiplier = multiplier * from_uint(10);
        }
        tmp_diff = tmp_diff * multiplier;
        while (tmp_lhs >= tmp_diff) {
            tmp_lhs = tmp_lhs - tmp_diff;

            lhs = lhs + multiplier;
        }
    }
}

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs) {
    for (int32_t i = 0; i < lhs.size; i++) {
        if (lhs.num[i] != rhs.num[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs) {
    return !(lhs == rhs);
}

bool operator<(const uint2022_t &lhs, const uint2022_t &rhs) {
    for (int32_t i = lhs.size - 1; i >= 0; i--) {
        if (lhs.num[i] > rhs.num[i]) {
            return false;
        }
        if (lhs.num[i] < rhs.num[i]) {
            return true;
        }
    }

    return false;
}

bool operator<=(const uint2022_t &lhs, const uint2022_t &rhs) {
    return !(lhs > rhs);
}

bool operator>(const uint2022_t &lhs, const uint2022_t &rhs) {
    for (int32_t i = lhs.size - 1; i >= 0; i--) {
        if (lhs.num[i] < rhs.num[i]) {
            return false;
        }
        if (lhs.num[i] > rhs.num[i]) {
            return true;
        }
    }

    return false;
}

bool operator>=(const uint2022_t &lhs, const uint2022_t &rhs) {
    return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value) {
    bool first_not_zero = 1;
    int32_t i;
    for (i = value.size - 1; i >= 0; i--) {
        if (value.num[i] != 0) {
            break;
        }
    }

    if (i < 0) {
        stream << 0;
    }

    for (; i >= 0; i--) {
        if (!first_not_zero) {
            int32_t digit_size = 0;
            uint64_t tmp = value.num[i];
            while (tmp > 0) {
                tmp /= 10;
                digit_size++;
            }
            for (int32_t j = 0; j < static_cast<int32_t>(value.digit_len) - digit_size; j++) {
                std::cout << 0;
            }
        }
        first_not_zero = 0;
        stream << value.num[i];
    }
    return stream;
}
