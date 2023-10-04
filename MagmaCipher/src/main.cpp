#include <iostream>
#include "MagmaCipher/MagmaCipher.h"

using namespace std;

int main() {
<<<<<<< HEAD
    string str = "aaa";
    long long arr[] {1,2};
    cout << sizeof(arr+1);
    cout << str << endl;
//    MagmaCipher magma;
//    magma.Encrypt();
//    magma.Decrypt();
//    cout << "Done" << endl;
=======
    MagmaCipher magma("1_2_3_4_5_6_7_8_9_0_r_o_f_l_a_n_");
    magma.Encrypt();
    magma.Decrypt();
    cout << "Done" << endl;

>>>>>>> d09985329f685e18c71d742193d436829ede55c6
    return 0;


}
