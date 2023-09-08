//
// Created by Kimihito on 07.09.2023.
//

#include "MagmaCipher.h"

#include <utility>

MagmaCipher::MagmaCipher() {
    this->filePath = R"(..\data\input.txt)";
    this->key = "1_2_3_4_5_6_7_8_9_0_r_o_f_l_a_n_";
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
    this->blocks.clear();
    std::ifstream in(this->filePath, std::ios::in);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(in), {});
    if(buffer.size()%8 != 0){
        cout << "Wrong size. Size must be %8 = 0" << endl;
    }

    //Split byte array to 64-bits blocks
    //Inserting them to array
    for(int i = 0; i < buffer.size(); i+=8) {
        this->blocks.emplace_back(buffer.begin(), buffer.begin() + 8);
    }
}

bool MagmaCipher::Encrypt() {
    Read();

    this->keyNumbers = GetKeyNumbers();

    for(vector<unsigned char>& block : blocks){
        //Two block parts here!
        vector<unsigned char> leftPart(block.begin(), block.begin() + block.size()/2);
        vector<unsigned char> rightPart(block.begin()+ block.size()/2, block.end());
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

vector<uint32_t> MagmaCipher::GetKeyNumbers() {
    //Splitted 256-bit key
    vector<unsigned char> key(this->key.begin(), this->key.end());

    //Getting subkeys K0-K7 here!
    vector<uint32_t> key_numbers;
    auto iter = key.begin();
    for(int i = 0; i < 8; i++){
        key_numbers.push_back(ReadU32(iter));
    }

    return key_numbers;
}
