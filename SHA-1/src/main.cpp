#include <iostream>
#include "SHA-1/SHA1.h"

int main() {

    SHA1 sha1;
    cout << sha1.GetHash() << endl;
    return 0;
}
