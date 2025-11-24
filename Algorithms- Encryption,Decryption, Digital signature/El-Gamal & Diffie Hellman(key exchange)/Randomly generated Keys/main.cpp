#include "el-dh.hpp"

int main() {
    ELGDH elgdh; 

    elgdh.diffieHellman();
    elgdh.elgamalEncryption();
    elgdh.elgamalSignature();

    return 0;
}
