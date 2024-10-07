#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include "SAES.h"
#include "Utils.h"



// This program assumes the keys "plaintext" and "key" are present in the input file.
int main()
{
    const std::string encryptionInputFilename = "InputEncryptSAES.txt";
    const std::string encryptionOutputFilename = "OutputEncryptSAES.txt";
    std::unordered_map<std::string, std::string> encryptionInputValues, encryptionOutputValues;
    uint16_t plaintext, ciphertext, key;


    try {
        encryptionInputValues = readKeyValues(encryptionInputFilename);
        plaintext = binaryStrToUint16(encryptionInputValues["plaintext"]);
        key = binaryStrToUint16(encryptionInputValues["key"]);

        std::cout << "Plaintext: " << encryptionInputValues["plaintext"] << std::endl;
        std::cout << "Key: " << encryptionInputValues["key"] << std::endl;

        // CODE HERE

        

        ciphertext = 65534;
        encryptionOutputValues["ciphertext"] = uint16ToBinaryStr(ciphertext);
        writeKeyValues(encryptionOutputFilename, encryptionOutputValues);

        std::cout << "Encrypted successfully.\n";
        std::cout << "Ciphertext saved in file " << encryptionOutputFilename << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Some error occurerd.\n";
    }


    return 0;
}

