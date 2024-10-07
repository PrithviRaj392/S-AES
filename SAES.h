#pragma once
#include <array>
#include <stdint.h>


class SAES
{
public:
    static constexpr uint8_t EXPANDED_KEY_SIZE_IN_NIBBLES = 12;
    static constexpr uint8_t BLOCK_SIZE_IN_NIBBLES = 4;
    using Block = std::array<uint8_t, BLOCK_SIZE_IN_NIBBLES>;


    static uint16_t encrypt(uint16_t plaintext, uint16_t key);
    static uint16_t decrypt(uint16_t ciphertext, uint16_t key);
    
    static std::array<uint8_t, EXPANDED_KEY_SIZE_IN_NIBBLES> expandKey(uint16_t key);
    
    static Block addRoundKey(Block value, uint16_t key);

    static Block substitueNibbles(Block value);
    static Block shiftRows(Block value);
    static Block mixColumns(Block value);

    static Block inverseSubstitueNibbles(Block value);
    static Block inverseShiftRows(Block value);
    static Block inverseMixColumns(Block value);


    static std::array<uint8_t, 4> getNibbles(uint16_t value); 



};
