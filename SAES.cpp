#include "SAES.h"

constexpr std::array<std::array<uint8_t, 2>, 2> SAES::ROUND_CONSTANTS;
constexpr std::array<uint8_t, 16> SAES::S_BOX;
constexpr std::array<uint8_t, 16> SAES::INVERSE_S_BOX;
constexpr std::array<std::array<uint8_t, 15>, 3> SAES::GF_MULTIPLICATION_TABLE;


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
    inverseSubstituteNibbles(state);

    // Inverse of Round 1
    addRoundKey(state, expandedKey[1]);
    inverseMixColumns(state);
    shiftRows(state);
    inverseSubstituteNibbles(state);

    addRoundKey(state, expandedKey[0]);

    return nibblesToUint16(state);
}


SAES::ExpandedKey SAES::expandKey(const SAES::Block& key)
{
    ExpandedKey expandedKey;

    expandedKey[0] = key;
    std::array<uint8_t, 2> W1 = { key[S01], key[S11] };
    std::array<uint8_t, 2> W0 = { key[S00], key[S10] };
    std::array<uint8_t, 2> GW1 =  gFunc(W1, 0);
    
    expandedKey[1][S00] = W0[0] ^ GW1[0];
    expandedKey[1][S10] = W0[1] ^ GW1[1];

    expandedKey[1][S01] = W1[0] ^ expandedKey[1][S00];
    expandedKey[1][S11] = W1[1] ^ expandedKey[1][S10];
    



    std::array<uint8_t, 2> W2 = { expandedKey[1][S00], expandedKey[1][S10] };
    std::array<uint8_t, 2> W3 = { expandedKey[1][S01], expandedKey[1][S11] };
    std::array<uint8_t, 2> GW3 =  gFunc(W3, 1);

    expandedKey[2][S00] = W2[0] ^ GW3[0];
    expandedKey[2][S10] = W2[1] ^ GW3[1];

    expandedKey[2][S01] = W3[0] ^ expandedKey[2][S00];
    expandedKey[2][S11] = W3[1] ^ expandedKey[2][S10];

    return std::move(expandedKey);
}
    
std::array<uint8_t, 2> SAES::gFunc(std::array<uint8_t, 2> value, uint8_t round) 
{
    // Rotate left by 1
    std::swap(value[0], value[1]);
    // Substitute nibbles
    value[0] = S_BOX[value[0]];
    value[1] = S_BOX[value[1]];
    // XOR with round constant
    value[0] ^= ROUND_CONSTANTS[round][0];
    value[1] ^= ROUND_CONSTANTS[round][1];

    return std::move(value);
}


void SAES::addRoundKey(SAES::Block& block, const SAES::Block& key)
{
    block[S00] ^= key[S00];
    block[S01] ^= key[S01];
    block[S10] ^= key[S10];
    block[S11] ^= key[S11];   
}


void SAES::substituteNibbles(SAES::Block& block)
{
    block[S00] = S_BOX[block[S00]];
    block[S01] = S_BOX[block[S01]];
    block[S10] = S_BOX[block[S10]];
    block[S11] = S_BOX[block[S11]];

}


void SAES::shiftRows(SAES::Block& block)
{
    // Row 0: No shift
    // Row 1: Shift left by 1
    std::swap(block[S10], block[S11]); // Swap S10 and S11

}


void SAES::mixColumns(SAES::Block& block)
{
    Block copy = block;

    /*
    [1   4][S00   S01] = [(1 * S00) XOR (4 * S10)   (1 * S01) XOR (4 * S11)]
    [4   1][S10   S11]   [(4 * S00) XOR (1 * S10)   (4 * S01) XOR (1 * S11)]
    */

    block[S00] = copy[S00] ^ GFMultiplication(FOUR, copy[S10]);
    block[S10] = GFMultiplication(FOUR, copy[S00]) ^ copy[S10];
    block[S01] = copy[S01] ^ GFMultiplication(FOUR, copy[S11]);
    block[S11] = GFMultiplication(FOUR, copy[S01]) ^ copy[S11];
}


void SAES::inverseSubstituteNibbles(SAES::Block& block)
{
    block[S00] = INVERSE_S_BOX[block[S00]];
    block[S01] = INVERSE_S_BOX[block[S01]];
    block[S10] = INVERSE_S_BOX[block[S10]];
    block[S11] = INVERSE_S_BOX[block[S11]];
    
}


void SAES::inverseMixColumns(SAES::Block& block)
{
    Block copy = block;

    /*
    [9   2][S00   S01] = [(9 * S00) XOR (2 * S10)   (9 * S01) XOR (2 * S11)]
    [2   9][S10   S11]   [(2 * S00) XOR (9 * S10)   (2 * S01) XOR (9 * S11)]
    */

    block[S00] = GFMultiplication(NINE, copy[S00]) ^ GFMultiplication(TWO, copy[S10]);
    block[S10] = GFMultiplication(TWO, copy[S00]) ^ GFMultiplication(NINE, copy[S10]);
    block[S01] = GFMultiplication(NINE, copy[S01]) ^ GFMultiplication(TWO, copy[S11]);
    block[S11] = GFMultiplication(TWO, copy[S01]) ^ GFMultiplication(NINE, copy[S11]);
}





uint8_t SAES::GFMultiplication(uint8_t valueIndex, uint8_t value)
{
    return GF_MULTIPLICATION_TABLE[valueIndex][value - 1];
}
