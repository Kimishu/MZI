#include <iostream>
#include "MagmaCipher/MagmaCipher.h"

using namespace std;

int main() {
    MagmaCipher magma;
    magma.Encrypt();

    cout << "Done" << endl;
    return 0;
}
