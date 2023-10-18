//
// Created by Kimihito on 16.10.2023.
//

#include "RabinCryptosystem.h"

RabinCryptosystem::RabinCryptosystem() {
    this->filePath = R"(..\data\input.txt)";
}

RabinCryptosystem::RabinCryptosystem(int p, int q): RabinCryptosystem() {
    if(!(IsPrime(p) && p % 4 == 3) && !(IsPrime(q) && q % 4 == 3)){
        cerr << "Use prime numbers!\n1. P and Q are prime numbers\n2. P mod 4 == 3 == Q mod 4" << endl;
        exit(1);
    }
    this->p = p;
    this->q = q;
}

RabinCryptosystem::RabinCryptosystem(string filePath) {
    this->filePath = std::move(filePath);
}

RabinCryptosystem::~RabinCryptosystem() {
    cout << "\nThanks for using Rabin Cryptosystem v1.0" <<
         "\nBy Kimihito" << endl;
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

        roots = EuclidAlgorithm(this->p,this->q);

        data.clear();
        for(unsigned short& number : extendedData){
            vector<unsigned short> unproofedRemainders = ChineseRemainderTheorem(number);
            vector<pair<unsigned char, unsigned char>> proofedRemainders;

            transform(unproofedRemainders.begin(), unproofedRemainders.end(), std::back_inserter(proofedRemainders),
                           [this](unsigned short& value) {
                               auto vec = GetBytes(value);
                               return std::make_pair(vec[0], vec[1]);
                           });
            for (const auto& splittedRemainder : proofedRemainders) {
                if (splittedRemainder.second == 0) {
                    data.push_back(splittedRemainder.first);
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

pair<uint32_t, uint32_t> RabinCryptosystem::EuclidAlgorithm(int p, int q) {
    int x0 = 1;
    int x1 = 0;

    int y0 = 0;
    int y1 = 1;

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

    double result = 1.0;

    for(int i = 0; i < k; i++){
        result = fmod((result * b),m);
    }

    return result;
}

vector<unsigned short> RabinCryptosystem::ChineseRemainderTheorem(unsigned short &number) {
    double m_p = ModularSqrt(number, (p + 1) / 4, p);
    double m_q = ModularSqrt(number, (q + 1) / 4, q);

    double x1 = fmod((roots.first * p * m_q + roots.second * q * m_p), (p * q));
    x1 = (x1 < 0) ? p*q + x1 : x1;
    double x2 = (p * q - x1);
    double x3 = fmod((roots.first * p * m_q - roots.second * q * m_p), (p * q));
    x3 = (x3 < 0) ? p * q + x3 : x3;
    double x4 = (p * q - x3);

    return vector<unsigned short>{
            (unsigned short)x1,
            (unsigned short)x2,
            (unsigned short)x3,
            (unsigned short)x4
    };
}

bool RabinCryptosystem::IsPrime(int &number) {
    if (number <= 1) {
        return false; // Числа меньше или равные 1 не являются простыми.
    }
    if (number <= 3) {
        return true; // 2 и 3 - простые числа.
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false; // Если число делится на 2 или 3 без остатка, оно не простое.
    }

    // Проверяем делителей, начиная с 5.
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }

    return true; // Если не найдено делителей, то число простое.
}


