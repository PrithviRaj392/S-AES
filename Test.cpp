#include <iostream>
#include "SAES.h"
#include "Utils.h"


// g++ Test.cpp SAES.cpp Utils.cpp -o Test && Test

int main()
{
    // 61606 = 1111 0000 1010 0110
    uint16_t testValue = 61606;
    std::cout << "Test Value: " << testValue << std::endl;

    SAES::Block nibbles = SAES::uint16ToNibbles(testValue);
    for (size_t i = 0; i < nibbles.size(); i++) {
        std::cout << "nibble " << i << " = " << (int)nibbles[i] << " = " << uint16ToBinaryStr(nibbles[i]) << std::endl;
    }
    
    uint16_t valueFromNibbles = SAES::nibblesToUint16(nibbles);
    std::cout << "Value From Nibbles: " << valueFromNibbles << std::endl;

    std::cout << std::endl;
    for(uint8_t i = 0; i < SAES::S_BOX_SIZE; i++) {
        std::cout << "Sbox " << (int)i << " = " << (int)SAES::Sbox[i];
        std::cout << ", InverseSbox = " << (int)SAES::inverseSbox[SAES::Sbox[i]] << std::endl; 
    }

    



    return 0;
}