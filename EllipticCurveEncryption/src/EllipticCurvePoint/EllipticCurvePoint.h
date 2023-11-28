//
// Created by Kimihito on 28.11.2023.
//

#ifndef ELLIPTICCURVEENCRYPTION_ELLIPTICCURVEPOINT_H
#define ELLIPTICCURVEENCRYPTION_ELLIPTICCURVEPOINT_H

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/mod_inverse.hpp>


namespace BigInteger {
    using namespace boost::multiprecision;
    using namespace boost::integer;

};

class EllipticCurvePoint {
public:
    BigInteger::cpp_int x, y, a, b, p;
    EllipticCurvePoint();
    EllipticCurvePoint(const EllipticCurvePoint& point);
    EllipticCurvePoint(BigInteger::cpp_int x, BigInteger::cpp_int y, BigInteger::cpp_int a, BigInteger::cpp_int b, BigInteger::cpp_int fieldChar);

    friend EllipticCurvePoint operator + (const EllipticCurvePoint& first, const EllipticCurvePoint& second);
    friend EllipticCurvePoint operator * (BigInteger::cpp_int& k, EllipticCurvePoint& p);
    friend bool operator ==(const EllipticCurvePoint& first, const EllipticCurvePoint& second);
    EllipticCurvePoint& operator = (const EllipticCurvePoint& point);
    static EllipticCurvePoint Double(EllipticCurvePoint& point);
    static EllipticCurvePoint Multiply(BigInteger::cpp_int number, EllipticCurvePoint point);
    static EllipticCurvePoint Add(EllipticCurvePoint first, EllipticCurvePoint second);
};


#endif //ELLIPTICCURVEENCRYPTION_ELLIPTICCURVEPOINT_H
