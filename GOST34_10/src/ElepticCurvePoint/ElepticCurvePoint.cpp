//
// Created by Kimihito on 19.11.2023.
//

#include "ElepticCurvePoint.h"

ElepticCurvePoint::ElepticCurvePoint()
        : x(BigInteger()), y(BigInteger()), a(BigInteger()), b(BigInteger()), fieldChar(BigInteger()) {}

ElepticCurvePoint::ElepticCurvePoint(const ElepticCurvePoint &point)
        : x(point.x), y(point.y), a(point.a), b(point.b), fieldChar(point.fieldChar){}

ElepticCurvePoint::ElepticCurvePoint(BigInteger x, BigInteger y, BigInteger a, BigInteger b, BigInteger fieldChar){
    this->x = x;
    this->y = y;
    this->a = a;
    this->b = b;
    this->fieldChar = fieldChar;
}


BigInteger ElepticCurvePoint::ModInverse(BigInteger &a, BigInteger m) {
    BigInteger m0 = m;
    BigInteger x0 = 0, x1 = 1;

    if (m == to_bigint(1))
        return 0;

    while (a > to_bigint(1)) {
        BigInteger q = a / m;
        BigInteger temp = m;
        m = a % m;
        a = temp;

        temp = x0;
        x0 = x1 - q * x0;
        x1 = temp;
    }

    // Нормализация ответа в пределах [0, m0)
    return (x1 % m0 + m0) % m0;
}

ElepticCurvePoint operator+(const ElepticCurvePoint &first, const ElepticCurvePoint &second) {
    ElepticCurvePoint p3;
    p3.a = first.a;
    p3.b = first.b;
    p3.fieldChar = first.fieldChar;

    BigInteger dy = second.y - first.y;
    BigInteger dx = second.x - first.x;

    if (dx < 0)
        dx += first.fieldChar;
    if (dy < 0)
        dy += first.fieldChar;

    BigInteger m = (dy * ElepticCurvePoint::ModInverse(dx, first.fieldChar)) % first.fieldChar;
    if (m < 0)
        m += first.fieldChar;
    p3.x = (m * m - first.x - second.x) % first.fieldChar;
    p3.y = (m * (first.x - p3.x) - first.y) % first.fieldChar;
    if (p3.x < 0)
        p3.x += first.fieldChar;
    if (p3.y < 0)
        p3.y += first.fieldChar;
    return p3;
}


ElepticCurvePoint ElepticCurvePoint::Double(ElepticCurvePoint &point) {
    ElepticCurvePoint p2;
    p2.a = point.a;
    p2.b = point.b;
    p2.fieldChar = point.fieldChar;

    BigInteger dy = 3 * point.x * point.x + point.a;
    BigInteger dx = 2 * point.y;

    if (dx < 0)
        dx += point.fieldChar;
    if (dy < 0)
        dy += point.fieldChar;

    BigInteger m = dy * ModInverse(dx,point.fieldChar) % point.fieldChar;
    p2.x = (m * m - point.x - point.x) % point.fieldChar;
    p2.y = (m * (point.x - p2.x) - point.y) % point.fieldChar;
    if (p2.x < 0)
        p2.x += point.fieldChar;
    if (p2.y < 0)
        p2.y += point.fieldChar;

    return p2;
}

ElepticCurvePoint ElepticCurvePoint::Multiply(BigInteger &number, ElepticCurvePoint &point) {
    ElepticCurvePoint temp = point;
    BigInteger tempX = number - 1;

    while (tempX != 0) {
        if ((tempX % to_bigint(2)) != to_bigint(0)) {
            if ((temp.x == point.x) || (temp.y == point.y))
                temp = Double(temp);
            else
                temp = temp + point;
            tempX = tempX - 1;
        }
        tempX /= 2;
        point = Double(point);
    }

    return temp;
}

ElepticCurvePoint &ElepticCurvePoint::operator=(const ElepticCurvePoint &point) {
    this->x = point.x;
    this->y = point.y;
    this->a = point.a;
    this->b = point.b;
    this->fieldChar = fieldChar;
    return *this;
}

ElepticCurvePoint operator*(BigInteger &k, ElepticCurvePoint &point) {
    return ElepticCurvePoint().Multiply(k,point);
}
