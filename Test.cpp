#include <iostream>
#include "SAES.h"
#include "Utils.h"


void printBlock(const SAES::Block& block)
{
    std::cout << uint16ToBinaryStr(block[SAES::S00]).substr(10, 19) << "    ";
    std::cout << uint16ToBinaryStr(block[SAES::S01]).substr(10, 19) << '\n';
    std::cout << uint16ToBinaryStr(block[SAES::S10]).substr(10, 19) << "    ";
    std::cout << uint16ToBinaryStr(block[SAES::S11]).substr(10, 19) << "\n\n";
}



// g++ Test.cpp SAES.cpp Utils.cpp -o Test && Test

int main()
{
    // 4 MSBs should always be zero because each value in a block represnets a nibble.
    SAES::Block block;
    
    block = SAES::uint16ToNibbles(0b0110111111001111);
    printBlock(block);

    SAES::mixColumns(block);
    printBlock(block);

    SAES::inverseMixColumns(block);
    printBlock(block);




    return 0;
}