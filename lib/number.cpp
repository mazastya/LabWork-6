#include "number.h"


uint2022_t from_uint(uint32_t i) {
    uint2022_t t = uint2022_t(i); 
    return t;
}

uint2022_t from_string(const char* buff) {
    uint2022_t result;
    std::string copy = buff;
    size_t pointer = UINT2022_BUFFER_SIZE-1;
    int length = copy.length();
    result.used = length % 9 == 0 ? length / 9 : (length / 9) + 1; 
    while (length >= 9)
    {
        for (int i = 9; i > 0; i--)
        {
            result.buffer[pointer] *= 10;
            result.buffer[pointer] += static_cast<int>(copy[length - i]) - static_cast<int>('0');           
        }
        copy.erase(length-9);
        length -= 9;
        pointer -= 1;
    }

    for (int i = copy.length(); i > 0; i--)
    {
        result.buffer[pointer] *= 10;
        result.buffer[pointer] += static_cast<int>(copy[length - i]) - '0';
    }
    return result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    int64_t remain = 0;
    int cnt = std::max(lhs.used, rhs.used);
    for (int i = UINT2022_BUFFER_SIZE-1; i >= UINT2022_BUFFER_SIZE-cnt; i--)
    {
        remain += lhs.buffer[i] + rhs.buffer[i];
        result.buffer[i] = remain % DIGIT_DIV;
        remain = remain / DIGIT_DIV;
    }
    result.used = cnt;
    if (remain > 0) {
        result.buffer[UINT2022_BUFFER_SIZE - (++result.used)] = remain;
    }
    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    int cnt = std::max(lhs.used, rhs.used);
    uint64_t remains = 0;
    result.used = cnt;
    for (int i = UINT2022_BUFFER_SIZE-1; i >= UINT2022_BUFFER_SIZE-cnt; i--)
    {
        uint64_t up = lhs.buffer[i] - remains;
        uint64_t down = rhs.buffer[i];
        if (up >= down) {
            result.buffer[i] = up - down;
            remains = 0;
        } else {
            result.buffer[i] = up + DIGIT_DIV - down;
            remains = 1;
        }
    }
    while(result.used > 1 && result.buffer[UINT2022_BUFFER_SIZE - result.used] == 0) {
            result.used--;
    }
    return result;
}

uint2022_t multiply(const uint2022_t& lhs, const uint32_t mnogitel, const int border) {
    uint2022_t result;
    if (mnogitel != 0 && border >= 0 && lhs.used > 0) {
        uint64_t overage = 0;
        result.used = border;
        for (int i = UINT2022_BUFFER_SIZE-1; i >= UINT2022_BUFFER_SIZE - lhs.used; i--)
        {
            uint64_t value = lhs.buffer[i];
            value *= mnogitel;
            value += overage;
            result.buffer[i-border] = value % DIGIT_DIV;
            result.used++;
            overage = value / DIGIT_DIV;
        }
        if (overage > 0) {
            result.used++;
            result.buffer[UINT2022_BUFFER_SIZE-result.used] = overage;
        }
    }
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    int border = 0;
    for (int i=UINT2022_BUFFER_SIZE-1; i>=UINT2022_BUFFER_SIZE-rhs.used; i--) {
        uint2022_t add = multiply(lhs, rhs.buffer[i], border++);
        result = result + add;
    }
    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs.used == rhs.used) {
        for (int i = UINT2022_BUFFER_SIZE-1; i >= UINT2022_BUFFER_SIZE-lhs.used; i--)
        {
            if (lhs.buffer[i] != rhs.buffer[i]) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    int first_digit = true;
    for (int i=UINT2022_BUFFER_SIZE-value.used; i<UINT2022_BUFFER_SIZE; i++) {
        if (first_digit) {
            stream << value.buffer[i];
            first_digit = false;
        } else {
            std::string str = std::to_string(value.buffer[i]);
            str.insert(0, 9-str.size(), '0');
            stream << str;
        }
    }
    return stream;
} 
