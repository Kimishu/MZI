//
// Created by Kimihito on 16.10.2023.
//

#ifndef RABINCRYPTOSYSTEM_RABINCRYPTOSYSTEM_H
#define RABINCRYPTOSYSTEM_RABINCRYPTOSYSTEM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class RabinCryptosystem {
    string filePath;
    int p,q;

    vector<unsigned char> data;
    pair<int, int> roots;

    bool IsPrime(int& number);

    //Converter functions
    uint16_t ReadU16(vector<unsigned char>::iterator iter);
    vector<unsigned char> GetBytes(uint16_t number);

    //Helpful algorithm functions
    vector<unsigned short> ChineseRemainderTheorem(unsigned short& number);
    pair<uint32_t, uint32_t> EuclidAlgorithm(int p, int q);
    double ModularSqrt(double b, double k, int m);

    ///Accepts bool value to encrypt/decrypt
    void Algorithm(bool mode);
    ///Reads data from file path to byte-array
    bool Read();
    ///Writes bytes to file path
    bool Write();
public:
    RabinCryptosystem();
    RabinCryptosystem(string filePath);
    RabinCryptosystem(int p, int q);
    ~RabinCryptosystem();

    ///Encrypts data
    bool Encrypt();
    ///Decrypts data
    bool Decrypt();

};


#endif //RABINCRYPTOSYSTEM_RABINCRYPTOSYSTEM_H
