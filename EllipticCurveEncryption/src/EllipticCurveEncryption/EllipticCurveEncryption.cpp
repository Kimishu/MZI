//
// Created by Kimihito on 28.11.2023.
//

#include "EllipticCurveEncryption.h"

#include <utility>

EllipticCurveEncryption::EllipticCurveEncryption() {
    this->filePath = R"(../data/input.txt)";
}

EllipticCurveEncryption::EllipticCurveEncryption(string filePath, EllipticCurvePoint ellipticCurvePoint) {
    this->filePath = std::move(filePath);
    this->ellipticCurvePoint = ellipticCurvePoint;
}

EllipticCurveEncryption::~EllipticCurveEncryption() {
}

vector<EllipticCurvePoint> EllipticCurveEncryption::Encrypt() {
    if(Read()) {
        EllipticCurvePoint M = ReadEllipticPoint(messageBytes);
        BigInteger::cpp_int k = RandomBigInteger(ellipticCurvePoint.p);
        EllipticCurvePoint C1 = EllipticCurvePoint::Multiply(k, ellipticCurvePoint);
        EllipticCurvePoint C2 = EllipticCurvePoint::Add(M, EllipticCurvePoint::Multiply(k, qPoint));
        encryptedPoints = {C1, C2};
        messageBytes.clear();
    }
    return encryptedPoints;
}

vector<unsigned char> EllipticCurveEncryption::Decrypt() {
    EllipticCurvePoint tempPoint = EllipticCurvePoint::Multiply(d, encryptedPoints[0]);
    tempPoint.y = -tempPoint.y;
    EllipticCurvePoint M = EllipticCurvePoint::Add(encryptedPoints[1], tempPoint);
    messageBytes = GetBytes(M);
    return messageBytes;
}

EllipticCurvePoint EllipticCurveEncryption::ReadEllipticPoint(vector<unsigned char> bytes) {
    vector<unsigned char> pBytes;
    BigInteger::export_bits(ellipticCurvePoint.p, std::back_inserter(pBytes), 8);
    std::reverse(pBytes.begin(), pBytes.end());

    uint32_t coordinateSize = pBytes.size();
    uint32_t minSize = 2;
    uint32_t maxSize = coordinateSize - minSize;
    if (bytes.size() > maxSize)
    {
        std::cout << "DLFSALFGSOL" << std::endl;
        exit(1);
    }
    uint32_t paddingSize = coordinateSize - bytes.size();
    vector<unsigned char> padding(paddingSize,0);
    vector<unsigned char> paddedMessage(bytes.begin(), bytes.end());
    paddedMessage.insert(paddedMessage.end(), padding.begin(), padding.end());
    paddedMessage[bytes.size()] = 0xff;
    BigInteger::cpp_int x;
    std::reverse(paddedMessage.begin(), paddedMessage.end());
    BigInteger::import_bits(x, paddedMessage.begin(), paddedMessage.end());
    return EllipticCurvePoint(x, BigInteger::cpp_int(0), ellipticCurvePoint.a, ellipticCurvePoint.b, ellipticCurvePoint.p);
}

vector<unsigned char> EllipticCurveEncryption::GetBytes(EllipticCurvePoint point) {
    vector<unsigned char> paddedMessage;
    BigInteger::export_bits(point.x, std::back_inserter(paddedMessage),8);
    std::reverse(paddedMessage.begin(), paddedMessage.end());

    int messageSize = 0;
    for (int i = 0; i < paddedMessage.size(); i++)
    {
        if (paddedMessage[i] == 0xff)
            messageSize = i;
    }
    return vector<unsigned char>(paddedMessage.begin(), paddedMessage.begin()+messageSize);
}

bool EllipticCurveEncryption::Read() {
    ifstream in(this->filePath, std::ios::in);
    messageBytes = vector<unsigned char>(std::istreambuf_iterator<char>(in), {});
    return !messageBytes.empty();
}

BigInteger::cpp_int EllipticCurveEncryption::RandomBigInteger(const boost::multiprecision::cpp_int &n) {
    // Инициализируем генератор случайных чисел Mersenne Twister
    boost::random::mt19937 gen(std::random_device{}());

    // Определяем равномерное распределение в диапазоне [0, n)
    boost::random::uniform_int_distribution<BigInteger::cpp_int> dist(0, n - 1);

    // Генерируем случайное число
    return dist(gen);
}
