//
// Created by Kimihito on 30.10.2023.
//

#include "SHA1.h"

SHA1::SHA1() {
    this->filePath = R"(..\data\input.txt)";
}

SHA1::SHA1(string filePath) {
    this->filePath = filePath;
}

SHA1::~SHA1() {
    cout << "Thanks for using SHA-1\nMade by Kimihito\n";
}

bool SHA1::Read() {
    ifstream in(filePath);
    vector<unsigned char> data(istreambuf_iterator<char>(in),{});
    if(data.empty())
        return false;
    int bitLength = data.size() * 8;
    //If data length greater than 512-bit(64 byte) then we split it to 512-bit blocks!
    if(data.size() >= 64){
        for(auto iter = data.begin(); iter != data.end(); iter = iter+64 < data.end() ? iter+64 : data.end()){
            blocks.emplace_back(iter, iter+64 < data.end() ? iter+64 : data.end());
        }
    } else {
        blocks.emplace_back(data);
    }
    //Adding a '1'-bit and then zeros to make last block length == 448-bit(56-byte)
    auto lastElement = blocks.back();
    lastElement.push_back(0x80);
    while(lastElement.size()%64 != 56){
        lastElement.push_back(0x00);
    }
    //Writing another 8 bytes
    vector<unsigned char> bitLengthBytes = GetBytes64(bitLength);
    reverse(bitLengthBytes.begin(), bitLengthBytes.end());
    lastElement.insert(lastElement.end(),bitLengthBytes.begin(), bitLengthBytes.end());
    blocks.back() = lastElement;
}

//TO DO
void SHA1::Addition() {

}

void SHA1::Algorithm() {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    for(vector<unsigned char>& block : blocks){
        vector<uint32_t> W = GetW(block);
        uint32_t a = h0,b = h1,c = h2,d = h3,e = h4;
        MainCycle(W, a,b,c,d,e);
        h0+=a;
        h1+=b;
        h2+=c;
        h3+=d;
        h4+=e;
    }

    vector<uint32_t> values = {h0, h1, h2, h3, h4};

    stringstream hashStringStream;

    // Используем поток для форматирования байтов в шестнадцатеричное представление
    for (auto value : values) {
        hashStringStream << std::hex << std::setw(8) << std::setfill('0') << value;
    }

    // Получаем строку с шестнадцатеричным представлением
    hash = hashStringStream.str();
}

string SHA1::GetHash() {
    if(Read()) {
        Algorithm();
        return hash;
    }
}

vector<unsigned char> SHA1::GetBytes64(uint64_t number) {
    vector<unsigned char> result;
    for (int i = 0; i < sizeof(uint64_t); i++) {
        unsigned char byte = (number >> (i * 8)) & 0xFF;
        result.push_back(byte);
    }
    return result;
}

vector<unsigned char> SHA1::GetBytes32(uint32_t number) {
    vector<unsigned char> result;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        unsigned char byte = (number >> (i * 8)) & 0xFF;
        result.push_back(byte);
    }
    return result;
}

std::uint32_t SHA1::ReadU32(vector<unsigned char>& vec) {
    uint32_t result = 0;
    memcpy(&result, vec.data(), sizeof(uint32_t));
    return result;
}

vector<uint32_t> SHA1::GetW(vector<unsigned char>& block) {
    vector<uint32_t> result;
    for(auto iter = block.begin(); iter != block.end(); iter+=4){
        auto vec = vector<unsigned char>(iter, iter+4);
        reverse(vec.begin(), vec.end());
        result.push_back(ReadU32(vec));
    }
    for(int i = result.size(); i < 80; i++){
        result.push_back(CyclicShift((result[i-3] ^ result[i-8] ^ result[i-14] ^ result[i-16]),1));
    }
    return result;
}

uint32_t SHA1::CyclicShift(uint32_t value, short n) {
    return (value << n) | (value >> (32- n));
}

void SHA1::MainCycle(vector<uint32_t>& W, uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t &e) {
    uint32_t k = 0, f = 0, temp;
    for(int i = 0; i < W.size(); i++){
        if(i >= 0 && i<= 19){
            f = (b & c) ^ ((~b) & d);
            k = 0x5A827999;
        } else if(i >= 20 && i <= 39){
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        } else if(i >= 40 && i <= 59){
            f = (b & c) ^ (b & d) ^ (c & d);
            k = 0x8F1BBCDC;
        } else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }
        temp = CyclicShift(a,5) + f + e + k + W[i];
        e = d;
        d = c;
        c = CyclicShift(b,30);
        b = a;
        a = temp;
    }
}

