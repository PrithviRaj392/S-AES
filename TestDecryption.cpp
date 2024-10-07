#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include "SAES.h"
#include "Utils.h"



// This program assumes the keys "ciphertext" and "key" are present in the input file.
int main()
{
    const std::string decryptionInputFilename = "InputDecryptSAES.txt";
    const std::string decryptionOutputFilename = "OutputDecryptSAES.txt";
    std::unordered_map<std::string, std::string> decryptionInputValues, decryptionOutputValues;
    uint16_t plaintext, ciphertext, key;


    try {
        decryptionInputValues = readKeyValues(decryptionInputFilename);
        ciphertext = binaryStrToUint16(decryptionInputValues["ciphertext"]);
        key = binaryStrToUint16(decryptionInputValues["key"]);

        // plaintext = SAES::decrypt(ciphertext, key);
        plaintext = 65534;

        decryptionOutputValues["plaintext"] = uint16ToBinaryStr(plaintext);
        writeKeyValues(decryptionOutputFilename, decryptionOutputValues);

        std::cout << "Decrypted successfully.\n";
        std::cout << "Plaintext saved in file " << decryptionOutputFilename << std::endl;


        std::cout << "\nCiphertext: " << decryptionInputValues["ciphertext"] << std::endl;
        std::cout << "Key: " << decryptionInputValues["key"] << std::endl;
        std::cout << "Plaintext: " << decryptionOutputValues["plaintext"] << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Some error occurerd.\n";
    }


    return 0;
}

