#pragma once
#include <array>
#include <cstdint>


class SAES
{
public:
    static constexpr uint8_t BLOCK_SIZE_IN_NIBBLES = 4;
    static constexpr uint8_t BLOCKS_IN_EXPANDED_KEY = 3;
    static constexpr uint8_t S_BOX_SIZE = 16;
    using Block = std::array<uint8_t, BLOCK_SIZE_IN_NIBBLES>;
    using ExpandedKey = std::array<Block, BLOCKS_IN_EXPANDED_KEY>;

    // sij = index of ith row and jth column in the state array
    static constexpr uint8_t s00 = 0;
    static constexpr uint8_t s10 = 1;
    static constexpr uint8_t s01 = 2;
    static constexpr uint8_t s11 = 3;

    static constexpr std::array<uint8_t, S_BOX_SIZE> Sbox = 
    {
        0b1001, 0b0100, 0b1010, 0b1011, 
        0b1101, 0b0001, 0b1000, 0b0101, 
        0b0110, 0b0010, 0b0000, 0b0011, 
        0b1100, 0b1110, 0b1111, 0b0111
    };

    static constexpr std::array<uint8_t, S_BOX_SIZE> inverseSbox = 
    {
        0b1010, 0b0101, 0b1001, 0b1011, 
        0b0001, 0b0111, 0b1000, 0b1111, 
        0b0110, 0b0000, 0b0010, 0b0011, 
        0b1100, 0b0100, 0b1101, 0b1110
    };


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


};




