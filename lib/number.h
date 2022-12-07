#pragma once
#include <cstring>
#include <cinttypes>
#include <iostream>
#include <string>

#define UINT2022_BUFFER_SIZE 68
#define MAX_UINT32 0xFFFFFFFF
#define DIGIT_DIV 1000000000

struct uint2022_t {
    uint2022_t() { 
        memset(buffer, 0, UINT2022_BUFFER_SIZE*sizeof(uint32_t)); 
        used = 1;
    }
    uint2022_t(const uint32_t& digit) {
        memset(buffer, 0, UINT2022_BUFFER_SIZE*sizeof(uint32_t));
        buffer[UINT2022_BUFFER_SIZE-1] = digit % DIGIT_DIV;
        buffer[UINT2022_BUFFER_SIZE-2] = digit / DIGIT_DIV;
        used = digit >= DIGIT_DIV ? 2 : 1;
    }
    uint2022_t(const uint2022_t& digit) {
        memcpy(buffer, digit.buffer, UINT2022_BUFFER_SIZE);
        used = digit.used;
    }
    size_t used;
    uint32_t buffer[UINT2022_BUFFER_SIZE];
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
