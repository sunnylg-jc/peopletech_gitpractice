#include<iostream>
#include<bitset>
int main()
{
    int num = 0b00110101;  //the bit that we are gonna perform toggling
    int bit_to_toggle;
    std::cout << "Enter the bit you want to toggle" << std::endl;
    std::cin >> bit_to_toggle;

    //creating a masked bit
    int masked_bit = (1 << bit_to_toggle);

    //toggling a bit
    int toggled_bit;
    toggled_bit = num ^ masked_bit;
    
    std::cout << "original bit is  "<< std::bitset<8>(num) << std::endl;
    std::cout << "masked bit is    "<< std::bitset<8>(masked_bit) << std::endl;
    std::cout << "               ^"  << std::endl;
    std::cout << "                 --------"  << std::endl;
    std::cout << "toggled bit is   "<< std::bitset<8>(toggled_bit) << std::endl;
    std::cout << "                 --------"  << std::endl;
    return 0;
}
