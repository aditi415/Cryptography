#include "caesar.hpp"
#include <cctype>

// Constructor
CaesarCipher::CaesarCipher(int s) {
    shift = s % 26;  // keep shift within [0,25]
}

// Encrypt function
string CaesarCipher::encrypt(const string& text) {
    string result = "";
    for (char c : text) {
        if (isupper(c)) {
            result += char(int(c - 'A' + shift) % 26 + 'A');
        }
        else if (islower(c)) {
            result += char(int(c - 'a' + shift) % 26 + 'a');
        }
        else {
            result += c; // keep non-letters same
        }
    }
    return result;
}

// Decrypt function
string CaesarCipher::decrypt(const string& text) {
    string result = "";
    for (char c : text) {
        if (isupper(c)) {
            result += char(int((c - 'A' - shift + 26) % 26) + 'A');
        }
        else if (islower(c)) {
            result += char(int((c - 'a' - shift + 26) % 26) + 'a');
        }
        else {
            result += c;
        }
    }
    return result;
}

