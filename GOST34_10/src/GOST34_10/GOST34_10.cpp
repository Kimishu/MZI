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
    //Step 1
    BigInteger::cpp_int alpha("297153330664438582545270981670025452388498804319519989524690055046924203387");//BinaryToBigInteger(HexToBinary(GetHash()));
    //Step 2
    BigInteger::cpp_int e = alpha % q;
    if(e == 0)
        e = 1;
    //Step 3
    std::vector<unsigned char> result;
    for(BigInteger::cpp_int k, r,s; r == 0 || s == 0;) {
        k = BigInteger::cpp_int("37811213293344800760307336328815013718816515361317748964192073587060513227392");//RandomBigInteger(q);
        ElepticCurvePoint elepticCurvePoint = ElepticCurvePoint::Multiply(k, ElepticCurvePoint(xp, yp, a, b, p));
        r = elepticCurvePoint.x % q;
        s = (r*d + k*e) % q;
        cout << r << endl;
        cout << s << endl;
        std::vector<unsigned char> rBytes = GetBytesBigInteger(r);
        std::vector<unsigned char> sBytes = GetBytesBigInteger(s);
        rBytes.insert(rBytes.end(),sBytes.begin(), sBytes.end());
        result = rBytes;
    }
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

BigInteger::cpp_int GOST34_10::BinaryToBigInteger(const string &binary) {
    BigInteger::cpp_int res;
    for(int i = binary.size(); i >= 0; i--){
        res+= pow(BigInteger::cpp_int(2),binary.size() - i);
    }

    return res;
}

BigInteger::cpp_int GOST34_10::RandomBigInteger(const boost::multiprecision::cpp_int &n) {
    // Инициализируем генератор случайных чисел Mersenne Twister
    boost::random::mt19937 gen(std::random_device{}());

    // Определяем равномерное распределение в диапазоне [0, n)
    boost::random::uniform_int_distribution<BigInteger::cpp_int> dist(0, n - 1);

    // Генерируем случайное число
    return dist(gen);
}

std::vector<unsigned char> GOST34_10::GetBytesBigInteger(BigInteger::cpp_int value) {
    std::size_t byteSize = (BigInteger::msb(value) + 7) / 8;
    std::vector<unsigned char> result(byteSize);

    for (std::size_t i = 0; i < byteSize; ++i) {
        unsigned char byte = static_cast<unsigned char>((value >> (i * 8)) & 0xFF);
        result[i] = byte;
    }

    return result;
}
