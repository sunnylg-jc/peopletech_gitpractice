#include <iostream>
#include <bitset>

int main() {
    int num = 0b00000100; // 4 in decimal, 2nd bit is ON
    std::cout << "Original: " << std::bitset<8>(num) << std::endl;

    int bit_to_check = 2;
    bool is_bit_set = num & (1 << bit_to_check); // Check the 2nd bit

    if (is_bit_set) {
        std::cout << "Bit " << bit_to_check << " is ON" << std::endl;
    } else {
        std::cout << "Bit " << bit_to_check << " is OFF" << std::endl;
    }

    return 0;
}
