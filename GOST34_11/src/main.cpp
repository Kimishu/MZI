#include <iostream>
#include "GOST34_11/GOST34_11.h"



int main() {
    GOST34_11 gost;
    string s = gost.GetHash();
    cout << s << endl;
    return 0;
}
