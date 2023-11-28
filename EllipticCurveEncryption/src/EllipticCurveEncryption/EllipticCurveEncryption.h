//
// Created by Kimihito on 28.11.2023.
//

#ifndef ELLIPTICCURVEENCRYPTION_ELLIPTICCURVEENCRYPTION_H
#define ELLIPTICCURVEENCRYPTION_ELLIPTICCURVEENCRYPTION_H

#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_number_generator.hpp>
#include "../EllipticCurvePoint/EllipticCurvePoint.h"

using namespace std;

class EllipticCurveEncryption {
    string filePath;
    EllipticCurvePoint ellipticCurvePoint; //= EllipticCurvePoint(BigInteger::cpp_int(2),
//                                                               BigInteger::cpp_int("4018974056539037503335449422937059775635739389905545080690979365213431566280"),
//                                                               BigInteger::cpp_int(7),
//                                                               BigInteger::cpp_int("43308876546767276905765904595650931995942111794451039583252968842033849580414"),
//                                                               BigInteger::cpp_int("57896044618658097711785492504343953926634992332820282019728792003956564821041"));
    BigInteger::cpp_int d = BigInteger::cpp_int("47296044618658097711785492524343953912234992332820282019728792003956564821041");
    EllipticCurvePoint qPoint = EllipticCurvePoint::Multiply(d, ellipticCurvePoint);

    vector<unsigned char> messageBytes;

    //IO Methods
    bool Read();

    //Helpful methods
    EllipticCurvePoint ReadEllipticPoint(vector<unsigned char> bytes);
    vector<unsigned char> GetBytes(EllipticCurvePoint point);
    BigInteger::cpp_int RandomBigInteger(const boost::multiprecision::cpp_int &n);
public:
    vector<EllipticCurvePoint> encryptedPoints;
    EllipticCurveEncryption();
    explicit EllipticCurveEncryption(string filePath, EllipticCurvePoint ellipticCurvePoint);
    ~EllipticCurveEncryption();
    vector<EllipticCurvePoint> Encrypt();
    vector<unsigned char> Decrypt();
};


#endif //ELLIPTICCURVEENCRYPTION_ELLIPTICCURVEENCRYPTION_H
