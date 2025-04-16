#include <iostream>
#include <bitset>

int main() {
    int num = 0b00001100; // 12 in decimal
    std::cout << "Original: " << std::bitset<8>(num) << std::endl;

    int bit_to_toggle = 3;
    num = num ^ (1 << bit_to_toggle); // Toggle the 3rd bit

    std::cout << "Toggled : " << std::bitset<8>(num) << std::endl;

    return 0;
}
