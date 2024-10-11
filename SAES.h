#pragma once
#include <array>
#include <cstdint>
#include <utility>


class SAES
{
public:
    static constexpr uint8_t BLOCK_SIZE_IN_NIBBLES = 4;
    static constexpr uint8_t BLOCKS_IN_EXPANDED_KEY = 3;
    using Block = std::array<uint8_t, BLOCK_SIZE_IN_NIBBLES>;
    using ExpandedKey = std::array<Block, BLOCKS_IN_EXPANDED_KEY>;

    // sij = index of ith row and jth column in the state array
    static constexpr uint8_t S00 = 0;
    static constexpr uint8_t S10 = 1;
    static constexpr uint8_t S01 = 2;
    static constexpr uint8_t S11 = 3;

    // 2 Round constants. Each has 2 nibbles. (Hexadecimal)
    static constexpr std::array<std::array<uint8_t, 2>, 2> ROUND_CONSTANTS = 
    {{
        { 0x8, 0x0 }, 
        { 0x3, 0x0 }
    }};

    static constexpr std::array<uint8_t, 16> S_BOX = 
    {
        0b1001, 0b0100, 0b1010, 0b1011, 
        0b1101, 0b0001, 0b1000, 0b0101, 
        0b0110, 0b0010, 0b0000, 0b0011, 
        0b1100, 0b1110, 0b1111, 0b0111
    };

    static constexpr std::array<uint8_t, 16> INVERSE_S_BOX = 
    {
        0b1010, 0b0101, 0b1001, 0b1011, 
        0b0001, 0b0111, 0b1000, 0b1111, 
        0b0110, 0b0000, 0b0010, 0b0011, 
        0b1100, 0b0100, 0b1101, 0b1110
    };

    // Indices for multiplication.
    static constexpr uint8_t TWO = 0, FOUR = 1, NINE = 2;

    // Table for GF(2^4) multplication of 2, 4 and 9 with 1 - 15.
    static constexpr std::array<std::array<uint8_t, 15>, 3> GF_MULTIPLICATION_TABLE = 
    {{
        { 0x2, 0x4, 0x6, 0x8, 0xA, 0xC, 0xE, 0x3, 0x1, 0x7, 0x5, 0xB, 0x9, 0xF, 0xD }, 
        { 0x4, 0x8, 0xC, 0x3, 0x7, 0xB, 0xF, 0x6, 0x2, 0xE, 0xA, 0x5, 0x1, 0xD, 0x9 }, 
        { 0x9, 0x1, 0x8, 0x2, 0xB, 0x3, 0xA, 0x4, 0xD, 0x5, 0xC, 0x6, 0xF, 0x7, 0xE }
    }};

    
    static Block uint16ToNibbles(uint16_t value);
    static uint16_t nibblesToUint16(const Block& nibbles); 


    static uint16_t encrypt(uint16_t plaintext, uint16_t key);
    static uint16_t decrypt(uint16_t ciphertext, uint16_t key);
    
    static ExpandedKey expandKey(const Block& key);
    

    // Self inverse.
    static void addRoundKey(Block& block, const Block& key);

    static void substituteNibbles(Block& block);
    // Self inverse.
    static void shiftRows(Block& block);
    static void mixColumns(Block& block);

    static void inverseSubstituteNibbles(Block& block);
    static void inverseMixColumns(Block& block);


    static uint8_t GFMultiplication(uint8_t valueIndex, uint8_t value);

    static std::array<uint8_t, 2> gFunc(std::array<uint8_t, 2> value, uint8_t round);

};




