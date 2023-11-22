//
// Created by Kimihito on 19.11.2023.
//

#ifndef GOST34_10_ELEPTICCURVEPOINT_H
#define GOST34_10_ELEPTICCURVEPOINT_H


#include "../BigInteger/BigInteger.h"

class ElepticCurvePoint {
    BigInteger x, y, a, b, fieldChar;
    static BigInteger ModInverse(BigInteger& a, BigInteger m);
public:

    ElepticCurvePoint();
    ElepticCurvePoint(const ElepticCurvePoint& point);
    ElepticCurvePoint(BigInteger x, BigInteger y, BigInteger a, BigInteger b, BigInteger fieldChar);

    friend ElepticCurvePoint operator + (const ElepticCurvePoint& first, const ElepticCurvePoint& second);
    friend ElepticCurvePoint operator * (BigInteger& k, ElepticCurvePoint& p);
    ElepticCurvePoint& operator = (const ElepticCurvePoint& point);
    static ElepticCurvePoint Double(ElepticCurvePoint& point);
    static ElepticCurvePoint Multiply(BigInteger& number, ElepticCurvePoint& point);
};


#endif //GOST34_10_ELEPTICCURVEPOINT_H
