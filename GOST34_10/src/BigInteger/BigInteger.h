//
// Created by Kimihito on 15.11.2023.
//

#ifndef GOST34_10_BIGINTEGER_H
#define GOST34_10_BIGINTEGER_H

/*
    BigInteger.h

    BigInteger Library for C++

    MIT License

    Created by Roshan Gupta on 16-10-2020
    Copyright (c) 2020 Roshan Gupta

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>

// Macros for Programmer(User) use cases.

#define big_abs BigInteger::_big_abs
#define big_max BigInteger::_big_max
#define big_min BigInteger::_big_min
#define big_pow BigInteger::_big_pow
#define big_sqrt BigInteger::_big_sqrt
#define big_log2 BigInteger::_big_log2
#define big_log10 BigInteger::_big_log10
#define big_logwithbase BigInteger::_big_logwithbase
#define big_antilog2 BigInteger::_big_antilog2
#define big_antilog10 BigInteger::_big_antilog10
#define big_swap BigInteger::_big_swap
#define big_reverse BigInteger::_big_reverse
#define big_gcd BigInteger::_big_gcd
#define big_lcm BigInteger::_big_lcm
#define big_fact BigInteger::_big_fact
#define big_isPrime BigInteger::_big_isPrime
#define big_isPalindrome BigInteger::_big_isPalindrome
#define to_bigint BigInteger::_to_bigint
#define rand_bigint BigInteger::_rand_bigint

// Big Integer Class

class BigInteger {
private:
    std::string str; // only data memeber for strong Big Integer as String. [For signed int, str[0] = '-']


    // Function Definitions for Internal Uses

    static std::string trim(std::string);
    static std::string add(std::string, std::string);
    static std::string subtract(std::string, std::string);
    static std::string multiply(std::string, std::string);
    static std::string divide(std::string, std::string);

    static std::string mod(std::string, std::string);
    static std::string shortDivide(std::string, unsigned long long int);
    static std::string maximum(std::string, std::string);
    static bool is_maximum(std::string, std::string);
    static bool is_strictlyMaximum(std::string, std::string);
    static std::string minimum(std::string, std::string);
    static bool is_minimum(std::string, std::string);
    static bool is_strictlyMinimum(std::string, std::string);
    static bool is_bigint(std::string);

    // Public Property

    static std::string abs(std::string);
    static std::string pow(std::string, std::string);
    static std::string sqrt(std::string);
    static std::string log2(std::string);
    static std::string log10(std::string);
    static std::string logwithbase(std::string, std::string);
    static std::string antilog2(std::string);
    static std::string antilog10(std::string);
    static void swap(std::string&, std::string&);
    static std::string reverse(std::string);
    static std::string gcd(std::string, std::string);
    static std::string lcm(std::string, std::string);
    static std::string fact(std::string);
    static bool isPalindrome(std::string);
    static bool isPrime(std::string);


public:
    // Constructors for big int.
    BigInteger() {
        str = '0';  //default value
    }
    BigInteger(std::string s) {
        if(!is_bigint(s))
            throw std::runtime_error("Invalid Big Integer has been fed.");   // if the input string is not valid number.
        str = s;
    }

    BigInteger(const char* s){
        if(!is_bigint(s))
            throw std::runtime_error("Invalid Big Integer has been fed.");   // if the input string is not valid number.
        str = s;
    }

    BigInteger(long long int n) {
        str = std::to_string(n);
    }
    BigInteger(int n) {
        str = std::to_string(n);
    }
    BigInteger(long int n) {
        str = std::to_string(n);
    }
    BigInteger(const BigInteger &n) {
        str = n.str;
    }

    // operator overloading for output stream {<<}
    friend std::ostream &operator << (std::ostream& stream, const BigInteger &n) {
        stream << n.str;
        return stream;
    }

    // operator overloading for input stream {>>}
    friend std::istream &operator >> (std::istream& stream, BigInteger &n) {
        stream >> n.str;
        return stream;
    }

    /* Operator {+} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    BigInteger operator + (BigInteger const &n) {
        BigInteger ans;
        ans.str = add(str, n.str);
        return ans;
    }
    friend BigInteger operator + (BigInteger const &n1, int n2) {
        BigInteger ans;
        ans.str = add(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator + (int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = add(n2.str, std::to_string(n1));
        return ans;
    }
    friend BigInteger operator + (BigInteger const &n1, long int n2) {
        BigInteger ans;
        ans.str = add(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator + (long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = add(n2.str, std::to_string(n1));
        return ans;
    }
    friend BigInteger operator + (BigInteger const &n1, long long int n2) {
        BigInteger ans;
        ans.str = add(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator + (long long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = add(n2.str, std::to_string(n1));
        return ans;
    }

    // Extra shortcut feature

    BigInteger& operator += (BigInteger const n) {
        (*this).str = add((*this).str, n.str);
        return (*this);
    }



    /* Operator {-} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    BigInteger operator - (BigInteger const &n) {
        BigInteger ans;
        ans.str = subtract(str, n.str);
        return ans;
    }

    BigInteger operator - (BigInteger const &n) const {
        BigInteger ans;
        ans.str = subtract(str, n.str);
        return ans;
    }

    friend BigInteger operator - (BigInteger const &n1, int n2) {
        BigInteger ans;
        ans.str = subtract(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator - (BigInteger &n1, int n2) {
        BigInteger ans;
        ans.str = subtract(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator - (int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = subtract(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator - (BigInteger const &n1, long int n2) {
        BigInteger ans;
        ans.str = subtract(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator - (long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = subtract(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator - (BigInteger const &n1, long long int n2) {
        BigInteger ans;
        ans.str = subtract(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator - (long long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = subtract(std::to_string(n1), n2.str);
        return ans;
    }

    // Extra shortcut feature

    BigInteger& operator -= (BigInteger const n) {
        (*this).str = subtract((*this).str, n.str);
        return (*this);
    }

    /* Operator {*} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    BigInteger operator * (BigInteger const &n) {
        BigInteger ans;
        ans.str = multiply(str, n.str);
        return ans;
    }
    friend BigInteger operator * (BigInteger const &n1, int n2) {
        BigInteger ans;
        ans.str = multiply(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator * (int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = multiply(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator * (BigInteger const &n1, long int n2) {
        BigInteger ans;
        ans.str = multiply(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator * (long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = multiply(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator * (BigInteger const &n1, long long int n2) {
        BigInteger ans;
        ans.str = multiply(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator * (long long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = multiply(std::to_string(n1), n2.str);
        return ans;
    }
    // Extra shortcut feature

    BigInteger& operator *= (BigInteger const n) {
        (*this).str = multiply((*this).str, n.str);
        return (*this);
    }

    /* Operator {/} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    BigInteger operator / (BigInteger const &n) {
        BigInteger ans;
        ans.str = divide(str, n.str);
        return ans;
    }
    friend BigInteger operator / (BigInteger const &n1, int n2) {
        BigInteger ans;
        ans.str = divide(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator / (BigInteger  &n1, int n2) {
        BigInteger ans;
        ans.str = divide(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator / (int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = divide(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator / (BigInteger const &n1, long int n2) {
        BigInteger ans;
        ans.str = divide(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator / (long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = divide(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator / (BigInteger const &n1, long long int n2) {
        BigInteger ans;
        ans.str = divide(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator / (long long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = divide(std::to_string(n1), n2.str);
        return ans;
    }

    // Extra shortcut feature

    BigInteger& operator /= (BigInteger const n) {
        (*this).str = divide((*this).str, n.str);
        return (*this);
    }

    /* Operator {%} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    BigInteger operator % (BigInteger const &n) {
        BigInteger ans;
        ans.str = mod(str, n.str);
        return ans;
    }
    friend BigInteger operator % (BigInteger const &n1, int n2) {
        BigInteger ans;
        ans.str = mod(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator % (int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = mod(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator % (BigInteger const &n1, long int n2) {
        BigInteger ans;
        ans.str = mod(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator % (long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = mod(std::to_string(n1), n2.str);
        return ans;
    }
    friend BigInteger operator % (BigInteger const &n1, long long int n2) {
        BigInteger ans;
        ans.str = mod(n1.str, std::to_string(n2));
        return ans;
    }
    friend BigInteger operator % (long long int n1, BigInteger const &n2) {
        BigInteger ans;
        ans.str = mod(std::to_string(n1), n2.str);
        return ans;
    }

    // Extra shortcut feature

    BigInteger& operator %= (BigInteger const n) {
        (*this).str = mod((*this).str, n.str);
        return (*this);
    }

    BigInteger& operator=(const std::string& str) {
        if (!is_bigint(str)) {
            throw std::runtime_error("Invalid Big Integer has been fed."); // if the input string is not a valid number.
        }
        this->str = str;
        return *this;
    }

    BigInteger& operator = (long long int n){
        str = std::to_string(n);
        return *this;
    }

    BigInteger& operator = (int n){
        str = std::to_string(n);
        return *this;
    }

    BigInteger& operator = (long int n){
        str = std::to_string(n);
        return *this;
    }

    BigInteger& operator = (const BigInteger &n){
        str = n.str;
        return *this;
    }

    //-------------------------------------------------
    //------------Increment and Decrement--------------
    //-------------------------------------------------

    /* Operator {++} Overloadings
    for the pre incremention  */
    BigInteger& operator ++ () {
        (*this).str = add((*this).str, "1");
        return (*this);
    }
    /* Operator {++} Overloadings
    for the post incremention  */
    BigInteger operator ++ (int) {
        (*this).str = add((*this).str, "1");
        return (*this);
    }

    /* Operator {--} Overloadings
    for the pre decremention  */
    BigInteger& operator -- () {
        (*this).str = subtract((*this).str, "1");
        return (*this);
    }

    /* Operator {--} Overloadings
    for the post incremention  */
    BigInteger operator -- (int) {
        (*this).str = subtract((*this).str, "1");
        return (*this);
    }

    //-------------------------------------------------
    //------------Conditional Operators----------------
    //-------------------------------------------------

    /* Operator {>} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    bool operator > (BigInteger const &n) {
        return is_strictlyMaximum(str, n.str);
    }
    friend bool operator > (BigInteger const &n1, int n2) {
        return is_strictlyMaximum(n1.str, std::to_string(n2));
    }
    friend bool operator > (int n1, BigInteger const &n2) {
        return is_strictlyMaximum(std::to_string(n1), n2.str);
    }
    friend bool operator > (BigInteger const &n1, long int n2) {
        return is_strictlyMaximum(n1.str, std::to_string(n2));
    }
    friend bool operator > (long int n1, BigInteger const &n2) {
        return is_strictlyMaximum(std::to_string(n1), n2.str);
    }
    friend bool operator > (BigInteger const &n1, long long int n2) {
        return is_strictlyMaximum(n1.str, std::to_string(n2));
    }
    friend bool operator > (long long int n1, BigInteger const &n2) {
        return is_strictlyMaximum(std::to_string(n1), n2.str);
    }

    /* Operator {<} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    bool operator < (BigInteger const &n) {
        return is_strictlyMinimum(str, n.str);
    }
    friend bool operator < (BigInteger const &n1, int n2) {
        return is_strictlyMinimum(n1.str, std::to_string(n2));
    }
    friend bool operator < (BigInteger &n1, int n2) {
        return is_strictlyMinimum(n1.str, std::to_string(n2));
    }
    friend bool operator < (int n1, BigInteger const &n2) {
        return is_strictlyMinimum(std::to_string(n1), n2.str);
    }
    friend bool operator < (BigInteger const &n1, long int n2) {
        return is_strictlyMinimum(n1.str, std::to_string(n2));
    }
    friend bool operator < (long int n1, BigInteger const &n2) {
        return is_strictlyMinimum(std::to_string(n1), n2.str);
    }
    friend bool operator < (BigInteger const &n1, long long int n2) {
        return is_strictlyMinimum(n1.str, std::to_string(n2));
    }
    friend bool operator < (long long int n1, BigInteger const &n2) {
        return is_strictlyMinimum(std::to_string(n1), n2.str);
    }

    /* Operator {>=} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    bool operator >= (BigInteger const &n) {
        return is_maximum(str, n.str);
    }
    friend bool operator >= (BigInteger const &n1, int n2) {
        return is_maximum(n1.str, std::to_string(n2));
    }
    friend bool operator >= (int n1, BigInteger const &n2) {
        return is_maximum(std::to_string(n1), n2.str);
    }
    friend bool operator >= (BigInteger const &n1, long int n2) {
        return is_maximum(n1.str, std::to_string(n2));
    }
    friend bool operator >= (long int n1, BigInteger const &n2) {
        return is_maximum(std::to_string(n1), n2.str);
    }
    friend bool operator >= (BigInteger const &n1, long long int n2) {
        return is_maximum(n1.str, std::to_string(n2));
    }
    friend bool operator >= (long long int n1, BigInteger const &n2) {
        return is_maximum(std::to_string(n1), n2.str);
    }

    /* Operator {<=} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    bool operator <= (BigInteger const &n) {
        return is_minimum(str, n.str);
    }
    friend bool operator <= (BigInteger const &n1, int n2) {
        return is_minimum(n1.str, std::to_string(n2));
    }
    friend bool operator <= (int n1, BigInteger const &n2) {
        return is_minimum(std::to_string(n1), n2.str);
    }
    friend bool operator <= (BigInteger const &n1, long int n2) {
        return is_minimum(n1.str, std::to_string(n2));
    }
    friend bool operator <= (long int n1, BigInteger const &n2) {
        return is_minimum(std::to_string(n1), n2.str);
    }
    friend bool operator <= (BigInteger const &n1, long long int n2) {
        return is_minimum(n1.str, std::to_string(n2));
    }
    friend bool operator <= (long long int n1, BigInteger const &n2) {
        return is_minimum(std::to_string(n1), n2.str);
    }


    /* Operator {==} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    bool operator ==(BigInteger const &n) {
        return (*this).str == n.str;
    }
    friend bool operator == (BigInteger const &n1, int n2) {
        return n1.str == std::to_string(n2);
    }
    friend bool operator == (int n1, BigInteger const &n2) {
        return std::to_string(n1) == n2.str;
    }
    friend bool operator == (BigInteger const &n1, long int n2) {
        return n1.str == std::to_string(n2);
    }
    friend bool operator == (long int n1, BigInteger const &n2) {
        return std::to_string(n1) == n2.str;
    }
    friend bool operator == (BigInteger const &n1, long long int n2) {
        return n1.str == std::to_string(n2);
    }
    friend bool operator == (long long int n1, BigInteger const &n2) {
        return std::to_string(n1) == n2.str;
    }


    /* Operator {!=} Overloadings, for different kind of
    parameter for the programmer's convinience  */

    bool operator !=(BigInteger const &n) {
        return (*this).str != n.str;
    }
    friend bool operator != (BigInteger const &n1, int n2) {
        return n1.str != std::to_string(n2);
    }
    friend bool operator != (BigInteger &n1, int n2) {
        return n1.str != std::to_string(n2);
    }
    friend bool operator != (int n1, BigInteger const &n2) {
        return std::to_string(n1) != n2.str;
    }
    friend bool operator != (BigInteger const &n1, long int n2) {
        return n1.str != std::to_string(n2);
    }
    friend bool operator != (long int n1, BigInteger const &n2) {
        return std::to_string(n1) != n2.str;
    }
    friend bool operator != (BigInteger const &n1, long long int n2) {
        return n1.str != std::to_string(n2);
    }
    friend bool operator != (long long int n1, BigInteger const &n2) {
        return std::to_string(n1) != n2.str;
    }

    //-----------------------------------------------------------
    //--------Function Definitions for External Uses-------------
    //-----------------------------------------------------------


    static BigInteger _big_max(BigInteger &a, BigInteger &b) {     // returns the maximum value between two Big Integers.
        BigInteger ans;
        ans.str = maximum(a.str, b.str);
        return ans;
    }
    static BigInteger _big_min(BigInteger &a, BigInteger &b) {      // returns the minimum value between two Big Integers.
        BigInteger ans;
        ans.str = minimum(a.str, b.str);
        return ans;
    }
    static BigInteger _big_abs(BigInteger &a) {                 // returns the absolute value of Big Integer.
        BigInteger ans;
        ans.str = abs(a.str);
        return ans;
    }
    static BigInteger _big_pow(BigInteger &a, BigInteger &b) {      // returns the power value between two Big Integers i.e., a^b, ^ -> power
        BigInteger ans;
        ans.str = pow(a.str, b.str);
        return ans;
    }
    static BigInteger _big_sqrt(BigInteger &a) {                // returns the square root value of Big Integer.
        BigInteger ans;
        ans.str = sqrt(a.str);
        return ans;
    }
    static BigInteger _big_log2(BigInteger &a) {                // returns the log of Big Integer to the base of 2.
        BigInteger ans;
        ans.str = log2(a.str);
        return ans;
    }
    static BigInteger _big_log10(BigInteger &a) {               // returns the log of Big Integer to the base of 10.
        BigInteger ans;
        ans.str = log10(a.str);
        return ans;
    }
    static BigInteger _big_logwithbase(BigInteger &a, BigInteger &b) {  // returns the log of Big Integer(a) to the base of (b).
        BigInteger ans;
        ans.str = logwithbase(a.str, b.str);
        return ans;
    }
    static BigInteger _big_antilog2(BigInteger &a) {        // returns the antilog of Big Integer to the base of 2.
        BigInteger ans;
        ans.str = antilog2(a.str);
        return ans;
    }
    static BigInteger _big_antilog10(BigInteger &a) {       // returns the antilog of Big Integer to the base of 10.
        BigInteger ans;
        ans.str = antilog10(a.str);
        return ans;
    }
    static void _big_swap(BigInteger &a, BigInteger &b) {     // swaps the two Big Integers.
        swap(a.str, b.str);
    }
    static BigInteger _big_reverse(BigInteger &a) {             //Reverses the Big Integer.
        BigInteger ans;
        ans.str = reverse(a.str);
        return ans;
    }
    static BigInteger _big_gcd(BigInteger &a, BigInteger &b) {         // returns the gcd of Big Integers a and b.
        BigInteger ans;
        ans.str = gcd(a.str, b.str);
        return ans;
    }
    static BigInteger _big_lcm(BigInteger &a, BigInteger &b) {          // returns the lcm of Big Integers a and b.
        BigInteger ans;
        ans.str = lcm(a.str, b.str);
        return ans;
    }
    static BigInteger _big_fact(BigInteger &a) {                    // returns the factorial of Big Integer.
        BigInteger ans;
        ans.str = fact(a.str);
        return ans;
    }
    static bool _big_isPalindrome(BigInteger &a) {              // Check if the Big Integer is Palindromic Integer.
        return isPalindrome(a.str);
    }
    static bool _big_isPrime(BigInteger &a) {                   // Check if the Big Integer is Prime Integer.
        return isPrime(a.str);
    }

    // to biginteger functions

    static BigInteger _to_bigint(std::string s) {
        BigInteger ans;
        ans.str = s;
        return ans;
    }
    static BigInteger _to_bigint(int n) {
        BigInteger ans;
        ans.str = std::to_string(n);
        return ans;
    }
    static BigInteger _to_bigint(long int n) {
        BigInteger ans;
        ans.str = std::to_string(n);
        return ans;
    }
    static BigInteger _to_bigint(long long int n) {
        BigInteger ans;
        ans.str = std::to_string(n);
        return ans;
    }

    static BigInteger _rand_bigint(BigInteger min, BigInteger max){
        std::random_device rd;
        std::mt19937 generator(rd());

        // Определяем диапазон случайных чисел
        std::uniform_int_distribution<uint8_t> distribution(0, UCHAR_MAX);

        // Генерируем массив байтов
        std::string result;
        for(int i = 0; i < max.str.size(); i++){
            result+= std::to_string(distribution(generator));
        }

        // Создаем объект BigInteger из сгенерированных данных
        BigInteger bigInteger = result;

        // Выполняем операцию % (max - min) + min
        bigInteger %= (max - min);
        bigInteger += min;

        return bigInteger;
    }

};


#endif //GOST34_10_BIGINTEGER_H
