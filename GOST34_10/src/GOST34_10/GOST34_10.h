//
// Created by Kimihito on 14.11.2023.
//

#ifndef GOST34_10_GOST34_10_H
#define GOST34_10_GOST34_10_H

#include <utility>
#include "../GOST34_11/GOST34_11.h"
#include "../BigInteger/BigInteger.h"
#include "../ElepticCurvePoint/ElepticCurvePoint.h"

class GOST34_10 {
    std::string filePath;
    //Elliptic curve coefficients
    const int a = 7;
    BigInteger b = "43308876546767276905765904595650931995942111794451039583252968842033849580414";
    //Elliptic curve module
    BigInteger p = "57896044618658097711785492504343953926634992332820282019728792003956564821041";
    //Cyclic subgroup order
    BigInteger q = "57896044618658097711785492504343953927082934583725450622380973592137631069619";
    //Signature key
    BigInteger d = "55441196065363246126355624130324183196576709222340016572108097750006097525544";
    BigInteger xp = 2;
    BigInteger yp = "4018974056539037503335449422937059775635739389905545080690979365213431566280";
    ElepticCurvePoint pPoint;

    //Methods
    std::string GetHash();
    std::string HexToBinary(const std::string& hex);
    const char* HexToBinary(char c);
    BigInteger BinaryToBigInteger(const std::string& binary);
public:
    GOST34_10();
    GOST34_10(std::string filePath);
    ~GOST34_10();
    std::string GetSignature();
    bool IsValid();
};


#endif //GOST34_10_GOST34_10_H
