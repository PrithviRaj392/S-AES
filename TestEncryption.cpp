#include <iostream>
#include <stdexcept>
#include "SAES.h"
#include "Utils.h"



// This program assumes the keys "plaintext" and "key" are present in the input file.

int main()
{
    const std::string encryptionInputFilename = "InputEncryptSAES.txt";
    const std::string encryptionOutputFilename = "OutputEncryptSAES.txt";
    StringMap encryptionInputValues, encryptionOutputValues;
    uint16_t plaintext, ciphertext, key;
    

    try {
        encryptionInputValues = readKeyValuePairs(encryptionInputFilename);
        plaintext = binaryStrToUint16(encryptionInputValues["plaintext"]);
        key = binaryStrToUint16(encryptionInputValues["key"]);

        ciphertext = SAES::encrypt(plaintext, key);

        encryptionOutputValues["ciphertext"] = uint16ToBinaryStr(ciphertext);
        writeKeyValuePairs(encryptionOutputFilename, encryptionOutputValues);

        std::cout << "Encrypted successfully.\n";
        std::cout << "Ciphertext saved in file " << encryptionOutputFilename << std::endl;


        std::cout << "\nPlaintext: " << encryptionInputValues["plaintext"] << std::endl;
        std::cout << "Key: " << encryptionInputValues["key"] << std::endl;
        std::cout << "Ciphertext: " << encryptionOutputValues["ciphertext"] << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Some error occurerd.\n";
    }


    return 0;
}

