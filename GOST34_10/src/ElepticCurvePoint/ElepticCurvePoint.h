//
// Created by Kimihito on 19.11.2023.
//

#ifndef GOST34_10_ELEPTICCURVEPOINT_H
#define GOST34_10_ELEPTICCURVEPOINT_H


#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/integer/mod_inverse.hpp>


namespace BigInteger {
    using namespace boost::multiprecision;
    using namespace boost::integer;

};

class ElepticCurvePoint {

public:
    BigInteger::cpp_int x, y, a, b, p;
    ElepticCurvePoint();
    ElepticCurvePoint(const ElepticCurvePoint& point);
    ElepticCurvePoint(BigInteger::cpp_int x, BigInteger::cpp_int y, BigInteger::cpp_int a, BigInteger::cpp_int b, BigInteger::cpp_int fieldChar);

    friend ElepticCurvePoint operator + (const ElepticCurvePoint& first, const ElepticCurvePoint& second);
    friend ElepticCurvePoint operator * (BigInteger::cpp_int& k, ElepticCurvePoint& p);
    ElepticCurvePoint& operator = (const ElepticCurvePoint& point);
    static ElepticCurvePoint Double(ElepticCurvePoint& point);
    static ElepticCurvePoint Multiply(BigInteger::cpp_int number, ElepticCurvePoint point);
};


#endif //GOST34_10_ELEPTICCURVEPOINT_H
