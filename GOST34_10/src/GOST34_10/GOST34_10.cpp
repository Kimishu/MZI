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
    BigInteger::cpp_int alpha = BinaryToBigInteger(HexToBinary(GetHash())); //
    //Step 2
    BigInteger::cpp_int e = alpha % q;
    if(e == 0)
        e = 1;
    //Step 3
    for(BigInteger::cpp_int k, r,s; r == 0 || s == 0;) {
        k = RandomBigInteger(q); //BigInteger::cpp_int("37811213293344800760307336328815013718816515361317748964192073587060513227392");
        ElepticCurvePoint elepticCurvePoint = ElepticCurvePoint::Multiply(k, ElepticCurvePoint(xp, yp, a, b, p));
        r = elepticCurvePoint.x % q;
        s = (r*d + k*e) % q;
        //rBytes
        std::vector<unsigned char> rBytes;
        BigInteger::export_bits(r, std::back_inserter(rBytes), 8);
        //sBytes
        std::vector<unsigned char> sBytes;
        BigInteger::export_bits(s, std::back_inserter(sBytes), 8);
        while(rBytes.size() != (BigInteger::msb(q) + 7) / 8)
            rBytes.push_back(0);
        while(sBytes.size() != (BigInteger::msb(q) + 7) / 8)
            sBytes.push_back(0);

        std::reverse(rBytes.begin(), rBytes.end());
        std::reverse(sBytes.begin(), sBytes.end());
        rBytes.insert(rBytes.end(),sBytes.begin(), sBytes.end());
        signature = rBytes;
    }
    return string(signature.begin(), signature.end());
}

bool GOST34_10::IsValid() {
    vector<unsigned char> rBytes(signature.begin(), signature.begin()+(signature.size() / 2));
    std::reverse(rBytes.begin(), rBytes.end());
    BigInteger::cpp_int r;
    BigInteger::import_bits(r, rBytes.begin(), rBytes.end());

    vector<unsigned char> sBytes(signature.begin()+(signature.size()/2), signature.end());
    std::reverse(sBytes.begin(), sBytes.end());
    BigInteger::cpp_int s;
    BigInteger::import_bits(s, sBytes.begin(), sBytes.end());

    if(r <= 0 || r >= q || s <= 0 || s >= q){
        return false;
    }

    BigInteger::cpp_int alpha = BinaryToBigInteger(HexToBinary(GetHash()));
    BigInteger::cpp_int e = alpha % q;
    if(e == 0)
        e = 1;

    BigInteger::cpp_int v = BigInteger::mod_inverse(e, q);
    BigInteger::cpp_int z1 = s * v % q;
    BigInteger::cpp_int z2 = -1*r*v % q + q;

    ElepticCurvePoint Q = ElepticCurvePoint::Multiply(d, ElepticCurvePoint(xp, yp, a, b, p));
    ElepticCurvePoint first = ElepticCurvePoint::Multiply(z1, ElepticCurvePoint(xp, yp, a,b,p));
    ElepticCurvePoint second = ElepticCurvePoint::Multiply(z2, Q);
    ElepticCurvePoint C = first + second;
    BigInteger::cpp_int R = C.x % q;

    return  R == r;
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
    for(char i : hex)
        bin += HexToBinary(i);
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