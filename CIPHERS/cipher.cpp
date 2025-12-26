#include "cipher.hpp"
string CaesarCipher::encrypt(const string &text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (isupper(c))
            result += char((c - 'A' + shift) % 26 + 'A');
        else if (islower(c))
            result += char((c - 'a' + shift) % 26 + 'a');
        else
            result += c;
    }
    return result;
}
string CaesarCipher::decrypt(const string &text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (isupper(c))
            result += char((c - 'A' - shift + 26) % 26 + 'A');
        else if (islower(c))
            result += char((c - 'a' - shift + 26) % 26 + 'a');
        else
            result += c;
    }
    return result;
}


string VigenereCipher::encrypt(const string &text) {
    string result = "";
    int j = 0;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base + (toupper(key[j % key.size()]) - 'A')) % 26 + base);
            j++;
        } else {
            result += c;
        }
    }
    return result;
}

string VigenereCipher::decrypt(const string &text) {
    string result = "";
    int j = 0;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base - (toupper(key[j % key.size()]) - 'A') + 26) % 26 + base);
            j++;
        } else {
            result += c;
        }
    }
    return result;
}


string HillCipher::encrypt(const string &text) {
    string result = "";
    string cleanText = text;
    if (cleanText.size() % 2 != 0) cleanText += 'X'; // padding

    for (int i = 0; i < cleanText.size(); i += 2) {
        int a = toupper(cleanText[i]) - 'A';
        int b = toupper(cleanText[i + 1]) - 'A';
        int x = (key[0][0] * a + key[0][1] * b) % 26;
        int y = (key[1][0] * a + key[1][1] * b) % 26;
        result += char(x + 'A');
        result += char(y + 'A');
    }
    return result;
}

string HillCipher::decrypt(const string &text) {
    string result = "";
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = (det % 26 + 26) % 26;

    // Find modular inverse of determinant
    int detInv = -1;
    for (int i = 0; i < 26; i++) {
        if ((det * i) % 26 == 1) { detInv = i; break; }
    }
    if (detInv == -1) return "Invalid key for Hill Cipher!";

    
    vector<vector<int>> invKey(2, vector<int>(2));
    invKey[0][0] = ( key[1][1] * detInv) % 26;
    invKey[1][1] = ( key[0][0] * detInv) % 26;
    invKey[0][1] = (-key[0][1] * detInv + 26) % 26;
    invKey[1][0] = (-key[1][0] * detInv + 26) % 26;

    for (int i = 0; i < text.size(); i += 2) {
        int a = toupper(text[i]) - 'A';
        int b = toupper(text[i + 1]) - 'A';
        int x = (invKey[0][0] * a + invKey[0][1] * b) % 26;
        int y = (invKey[1][0] * a + invKey[1][1] * b) % 26;
        result += char(x + 'A');
        result += char(y + 'A');
    }
    return result;
}

