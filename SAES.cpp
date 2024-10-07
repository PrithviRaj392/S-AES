#include "SAES.h"

constexpr std::array<uint8_t, SAES::S_BOX_SIZE> SAES::Sbox;
constexpr std::array<uint8_t, SAES::S_BOX_SIZE> SAES::inverseSbox;


// value = b15 b14 b13 b12 b11 b10 b9 b8 b7 b6 b5 b4 b3 b2 b1 b0
// nibbles = { 0000 b15 b14 b13 b12, 0000 b11 b10 b9 b8, 0000 b7 b6 b5 b4, 0000 b3 b2 b1 b0 }
// The following functions are for converting value to nibbles 
// and vice versa in the above format.

SAES::Block SAES::uint16ToNibbles(uint16_t value)
{
    Block nibbles;

    // bits 12 - 15
    nibbles[0] = value >> 12;
    // bits 8 - 11
    nibbles[1] = (value >> 8) & 0xF;
    // bits 4 - 7
    nibbles[2] = (value >> 4) & 0xF;
    // bits 0 - 3
    nibbles[3] = value & 0xF;

    return std::move(nibbles);
}


uint16_t SAES::nibblesToUint16(const SAES::Block& nibbles)
{
    uint16_t value;

    value = nibbles[0];
    value <<= 4;
    value |= nibbles[1];
    value <<= 4;
    value |= nibbles[2];
    value <<= 4;
    value |= nibbles[3];

    return value;
}



uint16_t SAES::encrypt(uint16_t plaintext, uint16_t key)
{
    Block state = uint16ToNibbles(plaintext);
    Block keyNibbles = uint16ToNibbles(key);
    ExpandedKey expandedKey = expandKey(keyNibbles);

    addRoundKey(state, expandedKey[0]);

    // Round 1
    substituteNibbles(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, expandedKey[1]);

    // Round 2
    substituteNibbles(state);
    shiftRows(state);
    addRoundKey(state, expandedKey[2]);

    return nibblesToUint16(state);
}


uint16_t SAES::decrypt(uint16_t ciphertext, uint16_t key)
{
    Block state = uint16ToNibbles(ciphertext);
    Block keyNibbles = uint16ToNibbles(key);
    ExpandedKey expandedKey = expandKey(keyNibbles);

    // Inverse of Round 2
    addRoundKey(state, expandedKey[2]);
    shiftRows(state);
    substituteNibbles(state);

    // Inverse of Round 1
    addRoundKey(state, expandedKey[1]);
    mixColumns(state);
    shiftRows(state);
    substituteNibbles(state);

    addRoundKey(state, expandedKey[0]);

    return nibblesToUint16(state);
}


SAES::ExpandedKey SAES::expandKey(const SAES::Block& key)
{
    ExpandedKey expandedKey;


    return std::move(expandedKey);
}
    


void SAES::addRoundKey(SAES::Block& block, const SAES::Block& key)
{
    
}


void SAES::substituteNibbles(SAES::Block& block)
{

}


void SAES::shiftRows(SAES::Block& block)
{

}


void SAES::mixColumns(SAES::Block& block)
{

}


void SAES::inverseSubstituteNibbles(SAES::Block& block)
{

}


void SAES::inverseMixColumns(SAES::Block& block)
{

}

