#include "EllipticCurveEncryption/EllipticCurveEncryption.h"

int main() {
    EllipticCurveEncryption encryption;
    encryption.Encrypt();
    cout << "Encryption:" << endl;
    cout << "C1: (x:" << encryption.encryptedPoints[0].x << " y:" << encryption.encryptedPoints[0].y << ")" << endl;
    cout << "C2: (x:" << encryption.encryptedPoints[1].x << " y:" << encryption.encryptedPoints[1].y << ")" << endl;
    cout << "Decryption:" << endl;
    vector<unsigned char> decryptedMessage = encryption.Decrypt();
    cout << string(decryptedMessage.begin(), decryptedMessage.end()) << endl;

    return 0;
}
