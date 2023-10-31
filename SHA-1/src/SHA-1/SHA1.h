//
// Created by Kimihito on 30.10.2023.
//

#ifndef SHA_1_SHA1_H
#define SHA_1_SHA1_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

class SHA1 {
    string filePath;
    vector<vector<unsigned char>> blocks;
    string hash;

    bool Read();
    void Algorithm();
    void Addition();
    vector<uint32_t> GetW(vector<unsigned char>& block);
    static void MainCycle(vector<uint32_t>& W, uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d, uint32_t& e);

    //Helpful methods
    static vector<unsigned char> GetBytes64(uint64_t number);
    static vector<unsigned char> GetBytes32(uint32_t number);
    static uint32_t ReadU32(vector<unsigned char>& vec);
    static uint32_t CyclicShift(uint32_t value, short n);
public:
    SHA1();
    SHA1(string filePath);
    ~SHA1();

    string GetHash();


};


#endif //SHA_1_SHA1_H
