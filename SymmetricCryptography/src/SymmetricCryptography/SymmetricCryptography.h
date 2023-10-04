//
// Created by Kimihito on 03.10.2023.
//

#ifndef SYMMETRICCRYPTOGRAPHY_SYMMETRICCRYPTOGRAPHY_H
#define SYMMETRICCRYPTOGRAPHY_SYMMETRICCRYPTOGRAPHY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class SymmetricCryptography {
    string directoryPath;
    string key;
    vector<vector<unsigned char>> blocks;

    ///Returns 32-bit unsigned int (4 bytes)
    uint32_t ReadU32(vector<unsigned char>::iterator iter);

    ///Returns 4 bytes vector
    vector<unsigned char> GetBytes(uint32_t number);

    void Read();
    void Write();

    void Algorithm(bool mode);
public:
    SymmetricCryptography();
    ~SymmetricCryptography();

    ///Encrypts data and write it into output.txt at the same path
    bool Encrypt();

    ///Decrypts data and write it into output.txt at the same path
    bool Decrypt();
};


#endif //SYMMETRICCRYPTOGRAPHY_SYMMETRICCRYPTOGRAPHY_H
