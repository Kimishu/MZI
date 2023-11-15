//
// Created by Kimihito on 14.11.2023.
//

#include "GOST34_10.h"


GOST34_10::GOST34_10() {
    this->filePath = R"(..\data\input.txt)";
}

GOST34_10::GOST34_10(std::string filePath) {
    this->filePath = std::move(filePath);
}

GOST34_10::~GOST34_10() = default;

string GOST34_10::GetSignature() {
    string hash = GetHash();
    string binaryVec = HexToBinary(hash);
    BigInteger alpha = BinaryToBigInteger(binaryVec);
    BigInteger e = alpha % q;
    //BigInteger e = "20798893674476452017134061561508270130637142515379653289952617252661468872421";
    if(e == to_bigint(0))
        e = 1;
    BigInteger k = BigInteger::_rand_bigint(0,q);
    cout << endl;
    return "";
}

std::string GOST34_10::GetHash() {
    GOST34_11 gost3411(filePath);
    string result = gost3411.GetHash();
    return result;
}

const char* GOST34_10::HexToBinary(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

std::string GOST34_10::HexToBinary(const std::string& hex)
{
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
        bin += HexToBinary(hex[i]);
    return bin;
}

BigInteger GOST34_10::BinaryToBigInteger(const string &binary) {
    BigInteger res;
    for(int i = binary.size(); i >= 0; i--){
        BigInteger value = 2;
        BigInteger pow = to_string((binary.size() - i));
        res+= big_pow(value,pow);
    }

    return res;
}
