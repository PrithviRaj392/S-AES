#include "SAES.h"




std::array<uint8_t, 4> SAES::getNibbles(uint16_t value)
{
    std::array<uint8_t, 4> nibbles;

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

