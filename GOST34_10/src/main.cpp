#include <iostream>
#include "GOST34_10/GOST34_10.h"

using namespace std;

int main() {
    GOST34_10 gost3410;
    string signature = gost3410.GetSignature();
    cout << endl <<"Signature: " << signature << endl;
    cout << "Verified status: " << boolalpha << gost3410.IsValid() << endl;
    return 0;
}
