#include <iostream>
#include "MagmaCipher/MagmaCipher.h"

using namespace std;

int main() {
    MagmaCipher magma("1_2_3_4_5_6_7_8_9_0_r_o_f_l_a_n_");
    magma.Encrypt();
    magma.Decrypt();
    cout << "Done" << endl;

    return 0;


}
