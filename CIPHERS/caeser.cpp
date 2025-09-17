#include "caesar.hpp"
#include <cctype>

CaesarCipher::CaesarCipher(int s) {
    shift = s % 26; 
}

string CaesarCipher::encrypt(const string& text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base + shift) % 26+ base);
        } else {
            result += c; 
        }
    }
    return result;
}

string CaesarCipher::decrypt(const string& text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base - shift + 26) % 26+ base);
        } else {
            result += c;
        }
    }
    return result;
}

