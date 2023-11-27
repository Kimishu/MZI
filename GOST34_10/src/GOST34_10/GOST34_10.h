//
// Created by Kimihito on 14.11.2023.
//

#ifndef GOST34_10_GOST34_10_H
#define GOST34_10_GOST34_10_H

#include <utility>
#include <random>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/random_number_generator.hpp>
#include "../GOST34_11/GOST34_11.h"
#include "../ElepticCurvePoint/ElepticCurvePoint.h"

namespace BigInteger{
    using namespace boost::multiprecision;
    using namespace boost::integer;
}

class GOST34_10 {
    std::string filePath;
    vector<unsigned char> signature;
    //Elliptic curve coefficients
    const int a = 7;
    BigInteger::cpp_int b{"43308876546767276905765904595650931995942111794451039583252968842033849580414"};
    //Elliptic curve module
    BigInteger::cpp_int p{"57896044618658097711785492504343953926634992332820282019728792003956564821041"};
    //Cyclic subgroup order
    BigInteger::cpp_int q{"57896044618658097711785492504343953927082934583725450622380973592137631069619"};
    //Signature key
    BigInteger::cpp_int d{"55441196065363246126355624130324183196576709222340016572108097750006097525544"};
    BigInteger::cpp_int xp = 2;
    BigInteger::cpp_int yp{"4018974056539037503335449422937059775635739389905545080690979365213431566280"};

    //Methods
    std::string GetHash();
    std::string HexToBinary(const std::string& hex);
    const char* HexToBinary(char c);
    BigInteger::cpp_int BinaryToBigInteger(const std::string& binary);

    //Random generation for BigInteger
    BigInteger::cpp_int RandomBigInteger(const BigInteger::cpp_int& n);
public:
    GOST34_10();
    GOST34_10(std::string filePath);
    ~GOST34_10();
    std::string GetSignature();
    bool IsValid();
};


#endif //GOST34_10_GOST34_10_H
