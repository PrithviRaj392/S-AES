#pragma once

#include <fstream>
#include <string>
#include <bitset>
#include <unordered_map>
#include <stdexcept>
#include <cctype>
#include <cstdint>

using StringMap = std::unordered_map<std::string, std::string>;

bool fileExists(const std::string& filename);
StringMap readKeyValuePairs(const std::string& filename);
void writeKeyValuePairs(const std::string& filename, StringMap values);

uint16_t binaryStrToUint16(std::string& binaryStr);
std::string uint16ToBinaryStr(uint16_t value);

