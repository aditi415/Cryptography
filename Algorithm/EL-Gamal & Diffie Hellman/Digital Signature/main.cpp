#include "el-gamal.hpp"

int main() {
    ELGDH elgdh; 

    elgdh.diffieHellman();
    elgdh.elgamalEncryption();
    elgdh.elgamalSignature();

    return 0;
}

