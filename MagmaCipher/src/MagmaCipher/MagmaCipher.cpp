//
// Created by Kimihito on 07.09.2023.
//

#include "MagmaCipher.h"

MagmaCipher::MagmaCipher() {
    this->filePath = R"(..\data\input.txt)";
    this->key = "1_2_3_4_5_6_7_8_9_0_r_o_f_l_a_n_";
    this->keyNumbers = GetKeyNumbers();
}

[[maybe_unused]] MagmaCipher::MagmaCipher(string key) {
    this->filePath = R"(..\data\input.txt)";
    if(key.length() != 32) {
        cout << "Wrong key size. It must be 256-bits (32 byte)" << endl;
        exit(1);
    }
    this->key = move(key);
    this->keyNumbers = GetKeyNumbers();
}

MagmaCipher::MagmaCipher(string filePath, string key) {
    this->filePath = move(filePath);
    if(key.length() != 32) {
        cout << "Wrong key size. It must be 256-bits (32 byte)" << endl;
        exit(1);
    }
    this->key = move(key);
    this->keyNumbers = GetKeyNumbers();
}

MagmaCipher::~MagmaCipher() {
    cout << "\nThanks for using MagmaCipher v1.0" <<
            "\nBy Kimihito" << endl;
}

///Reads txt-file from path
void MagmaCipher::Read() {
    this->blocks.clear();
    ifstream in(this->filePath, std::ios::in);
    vector<unsigned char> buffer(std::istreambuf_iterator<char>(in), {});
    if(buffer.size()%8 != 0){
        cout << "Wrong size. Data size must be multiple of 64-bits (8 bytes)" << endl;
        exit(-1);
    }

    //Split byte array to 64-bits blocks
    //Inserting them to array
    auto iter = buffer.begin();
    for(int i = 0; i < buffer.size(); i+=8) {
        this->blocks.emplace_back(iter, iter + 8);
        iter+=8;
    }
}

///This method writes an output data(encrypted/decrypted) into output.txt file
void MagmaCipher::Write() {
    ofstream out(R"(..\data\output.txt)", std::ios::out);
    string output;
    for(vector<unsigned char>& block: blocks){
        string temp(block.begin(), block.end());
        output+= temp;
    }

    if(out.is_open()){
        out << output;
        out.close();
    }
}

///Encrypts data from file
bool MagmaCipher::Encrypt() {
    Read();
    if(!blocks.empty()) {
        Algorithm(false);
        Write();
        return true;
    }
    cout << "Nothing to encrypt!" << endl;
    return false;
}

///Decrypts data from file
bool MagmaCipher::Decrypt() {
    if(!blocks.empty()) {
        Algorithm(true);
        Write();
        return true;
    }
    cout << "Nothing to decrypt!" << endl;
    return false;
}

///Takes byte-array iterator and returns uint32 (4 bytes)
std::uint32_t MagmaCipher::ReadU32(vector<unsigned char>::iterator iter) {
    std::vector<unsigned char> buffer(iter, iter + 4);
    uint32_t result = 0;
    memcpy(&result, buffer.data(), sizeof(uint32_t));
    return result;
}

///Takes uint32 number and converts it to byte array
vector<unsigned char> MagmaCipher::GetBytes(uint32_t number) {
    vector<unsigned char> result;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        unsigned char byte = (number >> (i * 8)) & 0xFF;
        result.push_back(byte);
    }
    return result;
}

///Splits 256-bit key to 8 uint32 subkeys
vector<uint32_t> MagmaCipher::GetKeyNumbers() {
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

///Takes uint32 number, splits it to 4 bytes and then takes value from S-block
uint32_t MagmaCipher::FeistelNet(uint32_t &data) {

    vector<unsigned char> bytes = GetBytes(data);

    for(int i = 0, j = 0; i < bytes.size(); i++){
        unsigned char byte = static_cast<int>(bytes[i]);
        unsigned char left = byte >> 4;
        unsigned char right = (byte << 28) >> 28;
        left = sBlocks[j++][left];
        right = sBlocks[j++][right];
        bytes[i] = ((left<<4)|right);
    }

    return ReadU32(bytes.begin());
}

///Takes bool value which means mode false - encrypt, true - decrypt
///@param mode - false(encrypt), true(decrypt)
void MagmaCipher::Algorithm(bool mode) {
    for(vector<unsigned char>& block : blocks){
        //Two block parts here!
        vector<unsigned char> leftBytes(block.begin(), block.begin() + block.size()/2);
        vector<unsigned char> rightBytes(block.begin()+ block.size()/2, block.end());

        uint32_t left = ReadU32(leftBytes.begin());
        uint32_t right = ReadU32(rightBytes.begin());

        for(int i = 0; i < 32; i++){
            int index = mode ? (i < 24 ? i%8 : 7 - i%8) : (i < 8 ? (i % 8) : (7 - i % 8));
            uint32_t result = (left^keyNumbers[index])%UINT32_MAX;
            FeistelNet(result);
            result = (result << 11) | (result >> 21);
            result^= right;

            if(i < 31){
                right = left;
                left = result;
            } else{
                right = result;
            }
        }

        vector<unsigned char> leftBytesResult = GetBytes(left);
        vector<unsigned char> rightBytesResult = GetBytes(right);
        leftBytesResult.insert(leftBytesResult.end(),rightBytesResult.begin(), rightBytesResult.end());

        block = leftBytesResult;
    }
}
