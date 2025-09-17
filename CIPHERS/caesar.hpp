#ifndef CAESAR_HPP
#define CAESAR_HPP

#include <string>
using namespace std;

class CaesarCipher {
public:
    CaesarCipher(int shift);

    string encrypt(const string& text);
    string decrypt(const string& text);

private:
    int shift;
};

#endif

