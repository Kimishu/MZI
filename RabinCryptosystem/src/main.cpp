#include "RabinCryptosystem/RabinCryptosystem.h"

int main() {
    RabinCryptosystem cryptosystem(239,283);
    cryptosystem.Encrypt();
    cryptosystem.Decrypt();
    return 0;
}
