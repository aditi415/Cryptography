#include <iostream>
#include "caesar.hpp"
using namespace std;

int main() {
    string text;
    int shift;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter shift value: ";
    cin >> shift;

    CaesarCipher cipher(shift);

    string encrypted = cipher.encrypt(text);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = cipher.decrypt(encrypted);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}

