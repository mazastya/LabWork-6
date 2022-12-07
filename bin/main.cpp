
#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t a = from_uint(2147483647);
    uint2022_t b = from_string("2147483647");

    for (int i=0; i<68; i++) {
        std::cout << a.buffer[i] << ' ';
    }
    std::cout << "\ta:" << a.used << "\n";

    for (int i=0; i<68; i++) {
        std::cout << b.buffer[i] << ' ';
    }
    std::cout << "\tb:" << b.used << "\n";

    std::cout << "a == b: " << (a == b) << std::endl;

    std::cout << "\ta:" << a << "\n";
    std::cout << "\tb:" << b << "\n";

    std::cout << "a * b: " << (a * b) << '\n';
    return 0;
}
