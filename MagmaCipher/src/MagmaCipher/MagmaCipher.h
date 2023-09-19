//
// Created by Kimihito on 07.09.2023.
//

#ifndef LAB1_MAGMACIPHER_H
#define LAB1_MAGMACIPHER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <codecvt>

using namespace std;

class MagmaCipher {

    string filePath;
    string key;
    vector<vector<unsigned char>> blocks;
    vector<uint32_t> keyNumbers;
    const vector<vector<short>>sBlocks = {
            {9,6,3,2,8,11,1,7,10,4,14,15,12,0,13,5},
            {3,7,14,9,8,10,15,0,5,2,6,12,11,4,13,1},
            {14,4,6,2,11,3,13,8,12,15,5,10,0,7,1,9},
            {14,7,10,12,13,1,3,9,0,2,11,4,15,8,5,6},
            {11,5,1,9,8,13,15,0,14,4,2,3,12,7,10,6},
            {3,10,13,12,1,2,0,11,7,5,9,4,8,15,14,6},
            {1,13,2,9,7,10,6,0,8,12,4,5,15,3,11,14},
            {11,10,15,5,0,12,14,8,6,2,3,9,1,7,13,4}
    };



    void Read();
    void Write();
    void Algorithm(bool mode);
    vector<uint32_t> GetKeyNumbers();
    static uint32_t ReadU32(vector<unsigned char>::iterator iter);
    vector<unsigned char> GetBytes(uint32_t number);
    uint32_t FeistelNet(uint32_t& data);

public:
    MagmaCipher();
    [[maybe_unused]] explicit MagmaCipher(string key);
    [[maybe_unused]] explicit MagmaCipher(string filePath, string key);

    ~MagmaCipher();
    bool Encrypt();
    bool Decrypt();
};


#endif //LAB1_MAGMACIPHER_H
