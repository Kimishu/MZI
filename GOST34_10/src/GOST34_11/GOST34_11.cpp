//
// Created by Kimihito on 31.10.2023.
//

#include "GOST34_11.h"

GOST34_11::GOST34_11() {
    this->filePath = R"(..\data\input.txt)";
}

GOST34_11::GOST34_11(string &filePath) {
    this->filePath = filePath;
}

GOST34_11::~GOST34_11() {
    cout << "Thanks for using GOST 34.11\nMade by Kimihito\n";
}

string GOST34_11::GetHash() {
    if(Read()){
        Algorithm();
        return hash;
    }
    return "";
}

bool GOST34_11::Read() {
    ifstream in(this->filePath);
    data = vector<unsigned char>(istreambuf_iterator<char>(in),{});
}

void GOST34_11::Algorithm() {
    vector<unsigned char> h(64, 0);
    vector<unsigned char> N(64, 0);
    vector<unsigned char> e(64, 0);
    vector<unsigned char> v_512(64, 0);
    v_512[1] = 0x02;

    while (data.size()/64 >= 1){
        vector<unsigned char> mInternal = vector<unsigned char>(data.end(),data.end()-64);
        h = g(N, h, mInternal);
        N = ModularPlus(N, v_512);
        e = ModularPlus(e, mInternal);
        data.erase(data.end(), data.end()-64);
    }
    vector<unsigned char> m(64 - data.size(),0);
    m[m.size()-1] = 0x01;
    m.insert(m.end(), data.begin(), data.end());
    h = g(N, h, m);
    vector<unsigned char> v_60(60, 0);
    vector<unsigned char> bytesDataSize = GetBytes(data.size());
    v_60.insert(v_60.end(), bytesDataSize.begin(), bytesDataSize.end());
    reverse(v_60.begin(), v_60.end());
    N = ModularPlus(N, v_60);
    e = ModularPlus(e, m);
    h = g(vector<unsigned char>(64,0), h, N);
    h = g(vector<unsigned char>(64,0), h, e);

    stringstream hashStringStream;

    for(unsigned char& byte : h){
        hashStringStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    hash = hashStringStream.str();
}

vector<unsigned char> GOST34_11::XOR(vector<unsigned char> &a, vector<unsigned char> &b) {
    vector<unsigned char> result(64, 0);
    for(int i = 0; i < result.size(); i++){
        result[i] = (unsigned char)(a[i]^b[i]);
    }
    return result;
}

vector<unsigned char> GOST34_11::ModularPlus(vector<unsigned char> &a, vector<unsigned char> &b) {
    vector<unsigned char> result(64, 0);
    int sum = 0;
    for(int i = 0; i < result.size(); i++){
        sum = a[i] + b[i] + (sum >> 8);
        result[i] = (unsigned char)(sum & 0xff);
    }
    return result;
}

vector<unsigned char> GOST34_11::P(vector<unsigned char> a) {
    vector<unsigned char> reversedTau = tau;
    reverse(reversedTau.begin(), reversedTau.end());
    vector<unsigned char> result;
    for(const auto& element: reversedTau){
        result.push_back(a[element]);
    }
    return result;
}

vector<unsigned char> GOST34_11::S(vector<unsigned char> a) {
    vector<unsigned char> reversedA = a;
    reverse(reversedA.begin(), reversedA.end());
    vector<unsigned char> result;
    for(const auto& element: reversedA){
        result.push_back(Pi[element]);
    }
    return result;
}

vector<unsigned char> GOST34_11::L(vector<unsigned char> a) {
   vector<unsigned char> newA(64, 0);
   int i, j, k, n, p;
   for(i = 7; i >= 0; i--){
       for(n = 0; n < 8; n++){
           p = 63;
           for(j = 7; j >= 0; j--){
               for(k = 0; k < 8; k++){
                   if(((a[i*8+j] >> k)&1)!=0){
                       newA[i*8+n] ^= l[p*8 + n];
                   }
                   p--;
               }
           }
       }
   }
    return newA;
}

vector<unsigned char> GOST34_11::LPS(vector<unsigned char> &a) {
    return L(P(S(a)));
}

vector<unsigned char> GOST34_11::E(vector<unsigned char> &k, vector<unsigned char> &m) {
    vector<unsigned char> result(64, 0);
    result = XOR(k, m);
    for(int i = 0; i < 12; i++){
        result = LPS(result);
        auto cValues = vector<unsigned char>(C.begin()+(i*64), C.begin()+(i*64)+64);
        k = XOR(k, cValues);
        k = LPS(k);
        result = XOR(k, result);
    }
    return result;
}

vector<unsigned char> GOST34_11::g(vector<unsigned char> N, vector<unsigned char> &h, vector<unsigned char> &m) {
    vector<unsigned char> result(64, 0);
    result = XOR(h, N);
    result = LPS(result);
    result = E(result, m);
    result = XOR(result, h);
    result = XOR(result, m);
    return result;
}

vector<unsigned char> GOST34_11::GetBytes(uint32_t number) {
    vector<unsigned char> result;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        unsigned char byte = (number >> (i * 8)) & 0xFF;
        result.push_back(byte);
    }
    return result;
}


