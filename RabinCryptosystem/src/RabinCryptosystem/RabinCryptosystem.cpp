//
// Created by Grimlock on 16.10.2023.
//

#include "RabinCryptosystem.h"

#include <utility>

RabinCryptosystem::RabinCryptosystem() {
    this->filePath = R"(..\data\input.txt)";
}

RabinCryptosystem::RabinCryptosystem(uint32_t p, uint32_t q): RabinCryptosystem() {
    this->p = p;
    this->q = q;
}

RabinCryptosystem::RabinCryptosystem(string filePath) {
    this->filePath = std::move(filePath);
}

RabinCryptosystem::RabinCryptosystem(string filePath, uint32_t p, uint32_t q) {
}

RabinCryptosystem::~RabinCryptosystem() {
    cout << "Done" << endl;
}

bool RabinCryptosystem::Read() {
    ifstream in(this->filePath);
    data = vector<unsigned char>(std::istreambuf_iterator<char>(in),{});
    if(data.empty())
        return false;
    return true;
}

bool RabinCryptosystem::Write() {
    if(data.empty())
        return false;
    ofstream out(this->filePath);
    for(unsigned char& byte: data){
        out << byte;
        cout << (::uint8_t)byte;
    }
    cout << endl;
    return true;
}

void RabinCryptosystem::Algorithm(bool mode) {

    //Get open key
    uint32_t openKey = p * q;

    vector<unsigned short> extendedData;
    if(mode){
        //Convert data from one byte-vector to two-byte vector
        for(unsigned char& byte : data){
            extendedData.push_back(static_cast<short>(byte));
        }

        //Encryption
        for(unsigned short& byte : extendedData){
            byte = (byte * byte) % openKey;
        }

        data.clear();
        for(unsigned short& number : extendedData){
            vector<unsigned char> result = GetBytes(number);
            data.insert(data.end(), result.begin(), result.end());
        }
    } else {
        //Reading two bytes
        auto iter = data.begin();
        for(int i = 0; i < data.size(); i+=2) {
            //Block size = 128 bit = 16 byte
            extendedData.push_back(ReadU16(iter));
            iter+=2;
        }

        cout << "Meme" << endl;
    }
}

bool RabinCryptosystem::Encrypt() {
    Read();
    Algorithm(true);
    Write();
    return false;
}

bool RabinCryptosystem::Decrypt() {
    Read();
    Algorithm(false);
    Write();
    return false;
}

uint16_t RabinCryptosystem::ReadU16(vector<unsigned char>::iterator iter) {
    std::vector<unsigned char> buffer(iter, iter + 2);
    uint16_t result = 0;
    memcpy(&result, buffer.data(), sizeof(uint16_t));
    return result;
}

///Takes uint32 number and converts it to byte array
vector<unsigned char> RabinCryptosystem::GetBytes(uint16_t number) {
    vector<unsigned char> result;
    for (int i = 0; i < sizeof(uint16_t); i++) {
        unsigned char byte = (number >> (i * 8)) & 0xFF;
        result.push_back(byte);
    }
    return result;
}

pair<uint32_t, uint32_t> RabinCryptosystem::EuclidAlgorithm() {
    uint32_t x0 = 1;
    uint32_t x1 = 0;

    uint32_t y0 = 0;
    uint32_t y1 = 1;

    while (q != 0)
    {
        uint32_t d = p / q;
        uint32_t r = p % q;

        p = q;
        q = r;

        uint32_t x = x0 - x1 * d;
        uint32_t y = y0 - y1 * d;

        x0 = x1;
        y0 = y1;
        x1 = x;
        y1 = y;
    }

    return make_pair(x0, y0);
}


