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
    }
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
            extendedData.push_back(ReadU16(iter));
            iter+=2;
        }


        pair<uint32_t, uint32_t> roots = EuclidAlgorithm(p,q);

        data.clear();
        for(unsigned short& number : extendedData){
            vector<unsigned short> shortVars = Decrypt(number);
            vector<pair<unsigned char, unsigned char>> vars;

            transform(shortVars.begin(), shortVars.end(), std::back_inserter(vars),
                           [this](unsigned short& value) {
                               auto vec = GetBytes(value);
                               return std::make_pair(vec[0], vec[1]);
                           });
            for (const auto& pair : vars) {
                if (pair.second == 0) {
                    data.push_back(pair.first);
                }
            }
        }
    }
}

bool RabinCryptosystem::Encrypt() {
    Read();
    Algorithm(true);
    Write();
    return false;
}

bool RabinCryptosystem::Decrypt() {
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

pair<uint32_t, uint32_t> RabinCryptosystem::EuclidAlgorithm(int p, int q) {
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

double RabinCryptosystem::ModularSqrt(double b, double k, int m) {
    int i = 0;
    double a = 1;
    vector<double> t;
    while (k > 0)
    {
        t.push_back(fmod(k, 2));
        k = (k - t[i]) / 2;
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        if (t[j] == 1)
        {
            a = fmod((a * b), m);
            b = fmod((b * b), m);
        }
        else
        {
            b = fmod((b * b), m);
        }
    }
    return a;
}

vector<unsigned short> RabinCryptosystem::Decrypt(unsigned short &number) {
    unsigned short m_p = ModularSqrt(number, (p + 1) / 4, p);
    unsigned short m_q = ModularSqrt(number, (q + 1) / 4, q);

    unsigned short x1 = (roots.first * p * m_q + roots.second * q * m_p) % (p * q);
    unsigned short x3 = (roots.first * p * m_q - roots.second * q * m_p) % (p * q);
    unsigned short x2 = (p * q - x1);
    unsigned short x4 = (p * q - x3);

    return vector<unsigned short>{
            static_cast<unsigned short>(x1 < 0 ? p*q + x1 : x1),
            x2,
            static_cast<unsigned short>(x3 < 0 ? p * q + x3 : x3),
            x4
    };
}


