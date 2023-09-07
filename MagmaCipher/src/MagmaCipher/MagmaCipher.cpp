//
// Created by Kimihito on 07.09.2023.
//

#include "MagmaCipher.h"

#include <utility>

MagmaCipher::MagmaCipher() {
    this->filePath = R"(..\data\input.txt)";
    this->key = "m_e_g_a_s_u_p_e_r_k_e_y_1_2_3_4!";
}

[[maybe_unused]] MagmaCipher::MagmaCipher(string key) {
    this->key = move(key);
}

MagmaCipher::MagmaCipher(string filePath, string key) {
    this->filePath = move(filePath);
    this->key = move(key);
}

MagmaCipher::~MagmaCipher() {

}

void MagmaCipher::Read() {
    this->buffer.clear();
    std::ifstream in(this->filePath, std::ios::in);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(in), {});
    this->buffer = buffer;
}

bool MagmaCipher::Encrypt() {
    Read();

    //Two block parts here!
    vector<unsigned char> leftPart(buffer.begin(), buffer.begin() + buffer.size()/2);
    vector<unsigned char> rightPart(buffer.begin()+buffer.size()/2, buffer.end());

    //Splitted 256-bit key
    vector<unsigned char> key(this->key.begin(), this->key.end());

    //Getting subkeys K0-K7 here!
    vector<uint32_t> key_numbers;
    vector<unsigned char>::iterator iter = key.begin();
    for(int i = 0; i < 8; i++){
        key_numbers.push_back(ReadU32(iter));
    }

    return false;
}

bool MagmaCipher::Decrypt() {
    Read();
    return false;
}

std::uint32_t MagmaCipher::ReadU32(vector<unsigned char>::iterator& iter) {
    std::vector<unsigned char> buffer(iter, iter + 4);
    iter += 4;
    uint32_t result = 0;
    memcpy(&result, buffer.data(), sizeof(uint32_t));
    return result;
}
