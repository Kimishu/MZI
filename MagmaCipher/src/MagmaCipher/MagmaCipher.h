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


    void Read();
    vector<uint32_t> GetKeyNumbers();

    static std::uint32_t ReadU32(vector<unsigned char>::iterator& iter);

public:
    MagmaCipher();
    [[maybe_unused]] explicit MagmaCipher(string filePath);
    [[maybe_unused]] explicit MagmaCipher(string filePath, string key);

    ~MagmaCipher();
    bool Encrypt();
    bool Decrypt();
};


#endif //LAB1_MAGMACIPHER_H
