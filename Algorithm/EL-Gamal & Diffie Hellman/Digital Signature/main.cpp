#include "el-gamal.hpp"

int main() {
    CryptoSystem crypto(32); 
    crypto.diffieHellman();
    crypto.elgamalEncryptDecrypt();
    crypto.elgamalSignature();
    return 0;
}

