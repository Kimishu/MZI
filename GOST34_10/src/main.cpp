#include "GOST34_10/GOST34_10.h"
#include <iostream>
#include "BigInteger/BigInteger.h"
using namespace std;

int main() {
//    GOST34_10 gost3410;
//    gost3410.GetSignature();
// P = (x, y)
// x = 2
    BigInteger k = "53854137677348463731403841147996619241504003434302020712960838528893196233395";
    BigInteger c = k*to_bigint(2);
    cout << c << endl;
    return 0;
}
