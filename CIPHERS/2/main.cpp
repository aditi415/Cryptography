#include "ciphers.hpp"
using namespace std;

int main() {
    Cipher c;
    c.caesar();
    c.vigenere();
    c.hill();
    return 0;
}

