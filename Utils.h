#pragma once

#include <fstream>
#include <string>
#include <bitset>
#include <unordered_map>
#include <stdexcept>
#include <cctype>
#include <cstdint>



bool fileExists(const std::string& filename);
std::unordered_map<std::string, std::string> readKeyValues(const std::string& filename);
void writeKeyValues(const std::string& filename, std::unordered_map<std::string, std::string> values);

uint16_t binaryStrToUint16(std::string& binaryStr);
std::string uint16ToBinaryStr(uint16_t value);

