//
// Created by Kimihito on 03.10.2023.
//

#include "SymmetricCryptography.h"

SymmetricCryptography::SymmetricCryptography() {
    //input path
    this->directoryPath = R"(..\data\input.txt)";
    //256-bit (32-byte) key
    this->key = "super__key__something__like_that";
    this->keyNumbers = GetKeyNumbers();
}

SymmetricCryptography::~SymmetricCryptography() {
    cout << "Thanks for using Symmetric Cryptography v1.0\n"
            "By Kimihito\n";
}

bool SymmetricCryptography::Encrypt() {
    Read();
    Algorithm(true);
    Write();
    return false;
}

bool SymmetricCryptography::Decrypt() {
    Algorithm(false);
    Write();
    return false;
}

///Takes byte-array iterator and returns uint32 (4 bytes)
std::uint32_t SymmetricCryptography::ReadU32(vector<unsigned char>::iterator iter) {
    std::vector<unsigned char> buffer(iter, iter + 4);
    uint32_t result = 0;
    memcpy(&result, buffer.data(), sizeof(uint32_t));
    return result;
}

///Takes uint32 number and converts it to byte array
vector<unsigned char> SymmetricCryptography::GetBytes(uint32_t number) {
    vector<unsigned char> result;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        unsigned char byte = (number >> (i * 8)) & 0xFF;
        result.push_back(byte);
    }
    return result;
}

vector<uint32_t> SymmetricCryptography::GetKeyNumbers() {
    //Splitted 256-bit key
    vector<unsigned char> key(this->key.begin(), this->key.end());

    //Getting subkeys K0-K7 here!
    vector<uint32_t> keyNumbers;
    auto iter = key.begin();
    for(int i = 0; i < 8; i++){
        keyNumbers.push_back(ReadU32(iter));
        iter+=4;
    }

    return keyNumbers;
}

uint32_t SymmetricCryptography::ModularPlus(uint32_t a, uint32_t b) {
    return (a+b)%UINT32_MAX;
}

uint32_t SymmetricCryptography::ModularMinus(uint32_t a, uint32_t b) {
    return (a-b)%UINT32_MAX;
}

void SymmetricCryptography::Read() {
    ifstream in(this->directoryPath, std::ios::in);
    vector<unsigned char> buffer(std::istreambuf_iterator<char>(in), {});

    vector<char> charsToRemove = {'\n', '\t'};

    buffer.erase(std::remove_if(buffer.begin(), buffer.end(), [&](char c) {
        return std::find(charsToRemove.begin(), charsToRemove.end(), c) != charsToRemove.end();
    }), buffer.end());

    if(buffer.size()%8 != 0){
        cerr << "Wrong block size!" << endl;
        exit(EXIT_FAILURE);
    }

    auto iter = buffer.begin();
    for(int i = 0; i < buffer.size(); i+=16) {
        //Block size = 128 bit = 16 byte
        this->blocks.emplace_back(iter, iter + 16);
        iter+=16;
    }

}

void SymmetricCryptography::Write() {
    ofstream out(R"(..\data\output.txt)", std::ios::out);
    string output;
    for(vector<unsigned char>& block: blocks){
        string temp(block.begin(), block.end());
        output+= temp + '\n';
    }

    if(out.is_open()){
        out << output;
        out.close();
    }
}

void SymmetricCryptography::Algorithm(bool mode) {

    for(vector<unsigned char>& block : blocks){
        uint32_t a = ReadU32(block.begin());
        uint32_t b = ReadU32(block.begin()+4);
        uint32_t c = ReadU32(block.begin()+8);
        uint32_t d = ReadU32(block.begin()+12);
        uint32_t e;

        if(mode) {
            for (int i = 1; i <= 8; i++) {
                b = b ^ GTransform(ModularPlus(a, keyNumbers[(7 * i - 6) % 8]), 5);
                c = c ^ GTransform(ModularPlus(d, keyNumbers[(7 * i - 5) % 8]), 21);
                a = ModularMinus(a, GTransform(ModularPlus(b, keyNumbers[(7 * i - 4) % 8]), 13));
                e = GTransform(ModularPlus(b, ModularPlus(c, keyNumbers[(7 * i - 3) % 8])), 21) ^ (i);
                b = ModularPlus(b, e);
                c = ModularMinus(c, e);
                d = ModularPlus(d, GTransform(ModularPlus(c, keyNumbers[(7 * i - 2) % 8]), 13));
                b = b ^ GTransform(ModularPlus(a, keyNumbers[(7 * i - 1) % 8]), 21);
                c = c ^ GTransform(ModularPlus(d, keyNumbers[(7 * i) % 8]), 5);

                swap(a, b);
                swap(c, d);
                swap(b, c);
            }

            auto bVector = GetBytes(b);
            auto dVector = GetBytes(d);
            auto aVector = GetBytes(a);
            auto cVector = GetBytes(c);
            bVector.insert(bVector.end(), dVector.begin(), dVector.end());
            bVector.insert(bVector.end(), aVector.begin(), aVector.end());
            bVector.insert(bVector.end(), cVector.begin(), cVector.end());

            block = bVector;
        }
        else {
            for(int i = 8; i > 0; i--){
                b = b ^ GTransform(ModularPlus(a, keyNumbers[(7*i)%8]),5);
                c = c ^ GTransform(ModularPlus(d, keyNumbers[(7*i-1)%8]),21);
                a = ModularMinus(a, GTransform(ModularPlus(b, keyNumbers[(7*i-2)%8]),13));
                e = GTransform(ModularPlus(b, ModularPlus(c,keyNumbers[(7*i-3)%8])),21) ^ i;
                b = ModularPlus(b,e);
                c = ModularMinus(c,e);
                d = ModularPlus(d, GTransform(ModularPlus(c, keyNumbers[(7*i-4)%8]),13));
                b = b ^ GTransform(ModularPlus(a, keyNumbers[(7*i-5)%8]),21);
                c = c ^ GTransform(ModularPlus(d,keyNumbers[(7*i-6)%8]),5);

                swap(a,b);
                swap(c,d);
                swap(a,d);
            }

            auto bVector = GetBytes(b);
            auto dVector = GetBytes(d);
            auto aVector = GetBytes(a);
            auto cVector = GetBytes(c);

            cVector.insert(cVector.end(), aVector.begin(), aVector.end());
            cVector.insert(cVector.end(), dVector.begin(), dVector.end());
            cVector.insert(cVector.end(), bVector.begin(), bVector.end());
            block = cVector;
        }
    }
}

uint32_t SymmetricCryptography::CyclicShift(uint32_t value, short n) {
    return (value << n) | (value >> (32- n));
}

uint32_t SymmetricCryptography::GTransform(uint32_t value, short n) {
    return CyclicShift(H(value), n);
}

uint32_t SymmetricCryptography::H(uint32_t value) {
    //Splitting uint32_t to vector of 4 bytes
    vector<unsigned char> bytes = GetBytes(value);

    for(uint32_t byte: bytes){
        uint32_t left = byte >> 4;
        uint32_t right = (byte << 28) >> 28;
        byte = H_table[left][right];
    }
    return ReadU32(bytes.begin());
}
