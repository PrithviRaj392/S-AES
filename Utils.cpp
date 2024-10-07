#include "Utils.h"


bool fileExists(const std::string& filename) 
{
    std::fstream file(filename, std::ios::in);
    if (file.is_open()) {
        file.close();
        return true;
    }
    
    return false;
}


// This function assumes that key value pairs are in the below format:
// "key": "value"
StringMap readKeyValuePairs(const std::string& filename) 
{
    if (!fileExists(filename)) {
        throw std::runtime_error(filename + " does not exist.");
    }
    std::fstream file;
    file.open(filename, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening " + filename + ".");
    }

    StringMap values;
    std::string key, value, ignore;

    while (std::getline(file, ignore, '"')) {
        std::getline(file, key, '"');

        std::getline(file, ignore, '"');
        std::getline(file, value, '"');
        values[key] = value;
    }
    
    file.close();
    return std::move(values);
}


// Writes key value pairs in the following format:
// "key": "value"
void writeKeyValuePairs(const std::string& filename, StringMap values)
{
    std::fstream file;
    file.open(filename, std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening " + filename + ".");
    }

    for (StringMap::iterator it = values.begin(); it != values.end(); it++) {
        file << '"' << it->first << "\": \"" << it->second << "\"\n";
    }

    file.close();
}


// Function to convert a binary string with maximum 16 binary digits to a
// 16 bit unsigned integer. Spaces are ignored.
uint16_t binaryStrToUint16(std::string& binaryStr)
{
    std::string binaryStrWithoutSpaces;
    for (size_t i = 0; i < binaryStr.length(); i++) {
        if (binaryStr[i] == '0' || binaryStr[i] == '1') {
            binaryStrWithoutSpaces += binaryStr[i];
        }
        else if (!std::isspace(binaryStr[i])) {
            throw std::runtime_error("Given string has a non binary character other than spaces.");
        }
    }
    if (binaryStrWithoutSpaces.length() > 16) {
        throw std::runtime_error("Given string has more than 16 binary digits.");
    }
    return std::stoi(binaryStrWithoutSpaces, nullptr, 2);
}


// Return a string representing binary of the given 16 bit unsigned integer
// with a space after every 4 bits. 
std::string uint16ToBinaryStr(uint16_t value)
{
    std::string binaryStr;
    // // 16 bits + 3 spaces = 19 total characters
    binaryStr.reserve(19);
    std::bitset<16> bits(value);

    for (int8_t i = 15; i >= 0; i--) {
        binaryStr += bits[i] ? '1' : '0';
        
        // Add a space after every 4 bits, but not after the last group
        if (i % 4 == 0 && i != 0) {
            binaryStr += ' ';
        }
    }

    return std::move(binaryStr);
}

