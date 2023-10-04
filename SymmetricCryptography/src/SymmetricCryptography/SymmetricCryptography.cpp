//
// Created by Kimihito on 03.10.2023.
//

#include "SymmetricCryptography.h"

SymmetricCryptography::SymmetricCryptography() {
    //input path
    this->directoryPath = R"(..\data\input.txt)";
    //256-bit (32-byte) key
    this->key = "super__key__something__like_that";
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

        
    }
}
