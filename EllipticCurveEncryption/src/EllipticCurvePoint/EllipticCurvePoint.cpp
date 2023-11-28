//
// Created by Kimihito on 28.11.2023.
//

#include "EllipticCurvePoint.h"

EllipticCurvePoint::EllipticCurvePoint()
        : x(BigInteger::cpp_int()), y(BigInteger::cpp_int()), a(BigInteger::cpp_int()), b(BigInteger::cpp_int()), p(BigInteger::cpp_int()) {}

EllipticCurvePoint::EllipticCurvePoint(const EllipticCurvePoint &point)
        : x(point.x), y(point.y), a(point.a), b(point.b), p(point.p){}

EllipticCurvePoint::EllipticCurvePoint(BigInteger::cpp_int x, BigInteger::cpp_int y, BigInteger::cpp_int a, BigInteger::cpp_int b, BigInteger::cpp_int p){
    this->x = x;
    this->y = y;
    this->a = a;
    this->b = b;
    this->p = p;
}

EllipticCurvePoint operator+(const EllipticCurvePoint &first, const EllipticCurvePoint &second) {
    EllipticCurvePoint p3;
    p3.a = first.a;
    p3.b = first.b;
    p3.p = first.p;

    BigInteger::cpp_int dy = second.y - first.y;
    BigInteger::cpp_int dx = second.x - first.x;

    if (dx < 0)
        dx += first.p;
    if (dy < 0)
        dy += first.p;

    BigInteger::cpp_int m = (dy * BigInteger::mod_inverse(dx, first.p)) % first.p;
    if (m < 0)
        m += first.p;
    p3.x = (m * m - first.x - second.x) % first.p;
    p3.y = (m * (first.x - p3.x) - first.y) % first.p;
    if (p3.x < 0)
        p3.x += first.p;
    if (p3.y < 0)
        p3.y += first.p;
    return p3;
}


EllipticCurvePoint EllipticCurvePoint::Double(EllipticCurvePoint &point) {
    EllipticCurvePoint p2;
    p2.a = point.a;
    p2.b = point.b;
    p2.p = point.p;

    BigInteger::cpp_int dy = 3 * point.x * point.x + point.a;
    BigInteger::cpp_int dx = 2 * point.y;

    if (dx < 0)
        dx += point.p;
    if (dy < 0)
        dy += point.p;
    auto mm = BigInteger::mod_inverse(dx,point.p);
    BigInteger::cpp_int m = dy * mm % point.p;
    p2.x = (m * m - point.x - point.x) % point.p;
    p2.y = (m * (point.x - p2.x) - point.y) % point.p;
    if (p2.x < 0)
        p2.x += point.p;
    if (p2.y < 0)
        p2.y += point.p;

    return p2;
}

EllipticCurvePoint EllipticCurvePoint::Multiply(BigInteger::cpp_int number, EllipticCurvePoint point) {
    EllipticCurvePoint temp = point;
    BigInteger::cpp_int tempX = number - 1;

    while (tempX != 0) {
        if ((tempX % 2) != 0) {
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

EllipticCurvePoint &EllipticCurvePoint::operator=(const EllipticCurvePoint &point) {
    this->x = point.x;
    this->y = point.y;
    this->a = point.a;
    this->b = point.b;
    this->p = p;
    return *this;
}

EllipticCurvePoint operator*(BigInteger::cpp_int &k, EllipticCurvePoint &point) {
    return EllipticCurvePoint().Multiply(k,point);
}

EllipticCurvePoint EllipticCurvePoint::Add(EllipticCurvePoint first, EllipticCurvePoint second) {
    EllipticCurvePoint C;
    C.a = first.a;
    C.b = first.b;
    C.p = first.p;

    BigInteger::cpp_int dx;
    BigInteger::cpp_int dy;

    if (first == second)
    {
        dy = 3 * first.x * first.x + first.a;
        dx = 2 * first.y;
    }
    else
    {
        dy = second.y - first.y;
        dx = second.x - first.x;
    }

    if (dx < 0)
        dx += first.p;
    if (dy < 0)
        dy += first.p;

    BigInteger::cpp_int m = dy * BigInteger::mod_inverse(dx,first.p) % first.p;
    if (m < 0)
        m += first.p;
    C.x = (m * m - first.x - second.x) % first.p;
    C.y = (m * (first.x - C.x) - first.y) % first.p;
    if (C.x < 0)
        C.x += first.p;
    if (C.y < 0)
        C.y += first.p;
    return C;
}

bool operator==(const EllipticCurvePoint &first, const EllipticCurvePoint &second) {
    if (first.x == second.x && first.y == second.y && first.p == second.p)
        return true;
    else
        return false;
}
