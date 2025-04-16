#include<iostream>
#include<bitset>
int main ()
{
    int n = 0b00010101;
    std::cout << std::bitset<8>(n) << std::endl;

    //input for checking
    int bit_to_check;
    std::cin >> bit_to_check;

    //creating a masked bit 
    int masked_bit;
    masked_bit = (1 << bit_to_check);
    std::cout << std::bitset<8>(masked_bit) << std::endl << std::endl;
    if  (bit_to_check > 7)
        std::cout << "please give the bit within the range i.e 0 to 7";

    //checking a bit
    if (n & masked_bit)
        std::cout << "the bit is set";
    else
        std::cout << "the bit is not set";

    
    return 0;
}
