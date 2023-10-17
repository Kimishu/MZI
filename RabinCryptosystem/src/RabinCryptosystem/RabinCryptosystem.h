//
// Created by Grimlock on 16.10.2023.
//

#ifndef RABINCRYPTOSYSTEM_RABINCRYPTOSYSTEM_H
#define RABINCRYPTOSYSTEM_RABINCRYPTOSYSTEM_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class RabinCryptosystem {
    string filePath;
    uint32_t p,q;

    vector<unsigned char> data;

    uint16_t ReadU16(vector<unsigned char>::iterator iter);
    vector<unsigned char> GetBytes(uint16_t number);

    ///Main algorithm
    pair<uint32_t, uint32_t> EuclidAlgorithm();
    void Algorithm(bool mode);
    bool Read();
    bool Write();
public:
    RabinCryptosystem();
    RabinCryptosystem(string filePath);
    RabinCryptosystem(uint32_t p, uint32_t q);
    RabinCryptosystem(string filePath, uint32_t p, uint32_t q);
    ~RabinCryptosystem();

    ///Encrypts data
    bool Encrypt();
    ///Decrypts data
    bool Decrypt();

};


#endif //RABINCRYPTOSYSTEM_RABINCRYPTOSYSTEM_H
